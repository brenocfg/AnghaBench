#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct eapol_sm {scalar_t__ suppPortStatus; TYPE_1__* ctx; scalar_t__ force_authorized_update; } ;
struct TYPE_2__ {int /*<<< orphan*/  ctx; int /*<<< orphan*/  (* port_cb ) (int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 scalar_t__ Authorized ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void eapol_sm_set_port_authorized(struct eapol_sm *sm)
{
	int cb;

	cb = sm->suppPortStatus != Authorized || sm->force_authorized_update;
	sm->force_authorized_update = FALSE;
	sm->suppPortStatus = Authorized;
	if (cb && sm->ctx->port_cb)
		sm->ctx->port_cb(sm->ctx->ctx, 1);
}