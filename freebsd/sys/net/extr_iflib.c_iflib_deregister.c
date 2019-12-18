#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kobj_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  TYPE_1__* if_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  ifc_media; int /*<<< orphan*/  ifc_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  STATE_LOCK_DESTROY (TYPE_1__*) ; 
 int /*<<< orphan*/  if_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_unregister_vlan_handlers (TYPE_1__*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobj_delete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
iflib_deregister(if_ctx_t ctx)
{
	if_t ifp = ctx->ifc_ifp;

	/* Remove all media */
	ifmedia_removeall(&ctx->ifc_media);

	/* Ensure that VLAN event handlers are unregistered */
	iflib_unregister_vlan_handlers(ctx);

	/* Release kobject reference */
	kobj_delete((kobj_t) ctx, NULL);

	/* Free the ifnet structure */
	if_free(ifp);

	STATE_LOCK_DESTROY(ctx);

	/* ether_ifdetach calls if_qflush - lock must be destroy afterwards*/
	CTX_LOCK_DESTROY(ctx);
}