#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* rpc_t ;
typedef  int /*<<< orphan*/ * rpc_app_t ;
typedef  TYPE_2__* iwdp_iwi_t ;
struct TYPE_5__ {int /*<<< orphan*/ * app; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  rpc_copy_app (int /*<<< orphan*/ * const,int /*<<< orphan*/ **) ; 

void rpc_set_app(rpc_t rpc, const rpc_app_t app) {
    iwdp_iwi_t iwi = (iwdp_iwi_t)rpc->state;
    rpc_app_t to_app = NULL;
    rpc_copy_app(app, &to_app);
    iwi->app = to_app;
}