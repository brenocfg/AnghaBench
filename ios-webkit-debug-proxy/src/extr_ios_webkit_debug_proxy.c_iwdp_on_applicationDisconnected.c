#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rpc_t ;
typedef  int /*<<< orphan*/  rpc_status ;
typedef  TYPE_1__* rpc_app_t ;
struct TYPE_3__ {int /*<<< orphan*/  app_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  iwdp_remove_app_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

rpc_status iwdp_on_applicationDisconnected(rpc_t rpc, const rpc_app_t app) {
  return iwdp_remove_app_id(rpc, app->app_id);
}