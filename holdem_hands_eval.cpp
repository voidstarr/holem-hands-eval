#include <node_api.h>
#include "SKPokerEval/SevenEval.h"

napi_value getRank(napi_env env, napi_callback_info args) {
  size_t argc = 7;
  napi_value argv[7];
  napi_status status;

  int32_t cards[7];

  status = napi_get_cb_info(env, args, &argc, argv, NULL, NULL);
  if (status != napi_ok) return nullptr;
  if (argc != 7) return nullptr;

  for(size_t i = 0; i < argc; i++) {
    status = napi_get_value_int32(env, argv[i], cards + i);
    if (status != napi_ok) return nullptr;
  }

  int32_t rank = SevenEval::GetRank(cards[0],cards[1],cards[2],cards[3],cards[4],cards[5],cards[6]);

  napi_value retValue;
  status = napi_create_int32(env, rank, &retValue);
  if (status != napi_ok) return nullptr;

  return retValue; 
}

napi_value init(napi_env env, napi_value exports) {
  napi_status status;
  napi_value fn;

  status = napi_create_function(env, nullptr, 0, getRank, nullptr, &fn);
  if (status != napi_ok) return nullptr;

  status = napi_set_named_property(env, exports, "getRank", fn);
  if (status != napi_ok) return nullptr;

  return exports;
}

NAPI_MODULE(NODE_GYP_MODULE_NAME, init)

