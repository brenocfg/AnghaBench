#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rpc_status ;
typedef  TYPE_1__* rpc_app_t ;
typedef  int /*<<< orphan*/ * plist_t ;
typedef  char* plist_dict_iter ;
typedef  int int8_t ;
struct TYPE_5__ {int /*<<< orphan*/  app_id; } ;

/* Variables and functions */
 scalar_t__ PLIST_DICT ; 
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 scalar_t__ calloc (size_t,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 size_t plist_dict_get_size (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  plist_dict_new_iter (int /*<<< orphan*/ * const,char**) ; 
 int /*<<< orphan*/  plist_dict_next_item (int /*<<< orphan*/ * const,char*,char**,int /*<<< orphan*/ **) ; 
 scalar_t__ plist_get_node_type (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  rpc_free_apps (TYPE_1__**) ; 
 int /*<<< orphan*/  rpc_parse_app (int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  strcmp (char*,int /*<<< orphan*/ ) ; 

rpc_status rpc_parse_apps(const plist_t node, rpc_app_t **to_apps) {
  if (!to_apps) {
    return RPC_ERROR;
  }
  *to_apps = NULL;
  if (plist_get_node_type(node) != PLIST_DICT) {
    return RPC_ERROR;
  }
  size_t length = plist_dict_get_size(node);
  rpc_app_t *apps = (rpc_app_t *)calloc(length + 1, sizeof(rpc_app_t));
  if (!apps) {
    return RPC_ERROR;
  }
  plist_dict_iter iter = NULL;
  plist_dict_new_iter(node, &iter);
  int8_t is_ok = (iter != NULL);
  size_t i;
  for (i = 0; i < length && is_ok; i++) {
    char *key = NULL;
    plist_t value = NULL;
    plist_dict_next_item(node, iter, &key, &value);
    rpc_app_t app = NULL;
    is_ok = (key && !rpc_parse_app(value, &app) &&
        !strcmp(key, app->app_id));
    apps[i] = app;
    free(key);
  }
  free(iter);
  if (!is_ok) {
    rpc_free_apps(apps);
    return RPC_ERROR;
  }
  *to_apps = apps;
  return RPC_SUCCESS;
}