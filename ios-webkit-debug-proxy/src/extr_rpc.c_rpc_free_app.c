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
struct rpc_app_struct {int dummy; } ;
typedef  TYPE_1__* rpc_app_t ;
struct TYPE_5__ {struct TYPE_5__* app_name; struct TYPE_5__* app_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

void rpc_free_app(rpc_app_t app) {
  if (app) {
    free(app->app_id);
    free(app->app_name);
    memset(app, 0, sizeof(struct rpc_app_struct));
    free(app);
  }
}