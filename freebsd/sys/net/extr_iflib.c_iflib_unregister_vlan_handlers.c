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
typedef  TYPE_1__* if_ctx_t ;
struct TYPE_3__ {int /*<<< orphan*/ * ifc_vlan_detach_event; int /*<<< orphan*/ * ifc_vlan_attach_event; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_DEREGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_config ; 
 int /*<<< orphan*/  vlan_unconfig ; 

__attribute__((used)) static void
iflib_unregister_vlan_handlers(if_ctx_t ctx)
{
	/* Unregister VLAN events */
	if (ctx->ifc_vlan_attach_event != NULL) {
		EVENTHANDLER_DEREGISTER(vlan_config, ctx->ifc_vlan_attach_event);
		ctx->ifc_vlan_attach_event = NULL;
	}
	if (ctx->ifc_vlan_detach_event != NULL) {
		EVENTHANDLER_DEREGISTER(vlan_unconfig, ctx->ifc_vlan_detach_event);
		ctx->ifc_vlan_detach_event = NULL;
	}

}