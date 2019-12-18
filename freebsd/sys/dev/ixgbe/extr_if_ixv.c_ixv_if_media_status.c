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
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct adapter {int link_speed; int /*<<< orphan*/  link_active; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10G_T ; 
 int IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
#define  IXGBE_LINK_SPEED_100_FULL 131 
#define  IXGBE_LINK_SPEED_10GB_FULL 130 
#define  IXGBE_LINK_SPEED_10_FULL 129 
#define  IXGBE_LINK_SPEED_1GB_FULL 128 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_if_media_status(if_ctx_t ctx, struct ifmediareq * ifmr)
{
	struct adapter *adapter = iflib_get_softc(ctx);

	INIT_DEBUGOUT("ixv_media_status: begin");

	iflib_admin_intr_deferred(ctx);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (!adapter->link_active)
		return;

	ifmr->ifm_status |= IFM_ACTIVE;

	switch (adapter->link_speed) {
		case IXGBE_LINK_SPEED_1GB_FULL:
			ifmr->ifm_active |= IFM_1000_T | IFM_FDX;
			break;
		case IXGBE_LINK_SPEED_10GB_FULL:
			ifmr->ifm_active |= IFM_10G_T | IFM_FDX;
			break;
		case IXGBE_LINK_SPEED_100_FULL:
			ifmr->ifm_active |= IFM_100_TX | IFM_FDX;
			break;
		case IXGBE_LINK_SPEED_10_FULL:
			ifmr->ifm_active |= IFM_10_T | IFM_FDX;
			break;
	}
}