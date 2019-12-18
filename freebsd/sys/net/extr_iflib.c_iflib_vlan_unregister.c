#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  if_t ;
typedef  scalar_t__ if_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTX_LOCK (scalar_t__) ; 
 int /*<<< orphan*/  CTX_UNLOCK (scalar_t__) ; 
 int IFCAP_VLAN_HWFILTER ; 
 int /*<<< orphan*/  IFDI_VLAN_UNREGISTER (scalar_t__,int) ; 
 int if_getcapenable (int /*<<< orphan*/ ) ; 
 scalar_t__ if_getsoftc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_if_init_locked (scalar_t__) ; 

__attribute__((used)) static void
iflib_vlan_unregister(void *arg, if_t ifp, uint16_t vtag)
{
	if_ctx_t ctx = if_getsoftc(ifp);

	if ((void *)ctx != arg)
		return;

	if ((vtag == 0) || (vtag > 4095))
		return;

	CTX_LOCK(ctx);
	IFDI_VLAN_UNREGISTER(ctx, vtag);
	/* Re-init to load the changes */
	if (if_getcapenable(ifp) & IFCAP_VLAN_HWFILTER)
		iflib_if_init_locked(ctx);
	CTX_UNLOCK(ctx);
}