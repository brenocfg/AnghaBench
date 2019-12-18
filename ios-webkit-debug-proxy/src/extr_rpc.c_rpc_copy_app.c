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
struct TYPE_5__ {int /*<<< orphan*/  is_proxy; void* app_name; void* app_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RPC_ERROR ; 
 int /*<<< orphan*/  RPC_SUCCESS ; 
 TYPE_1__* rpc_new_app () ; 
 void* strdup (void*) ; 

rpc_status rpc_copy_app(rpc_app_t app, rpc_app_t *to_app) {
  rpc_app_t new_app = (to_app ? rpc_new_app() : NULL);
  if (!new_app) {
    return RPC_ERROR;
  }

  new_app->app_id = strdup(app->app_id);
  new_app->app_name = strdup(app->app_name);
  new_app->is_proxy = app->is_proxy;
  *to_app = new_app;
  return RPC_SUCCESS;
}