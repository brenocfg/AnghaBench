#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u_char ;
struct ifmediareq {int ifm_active; int /*<<< orphan*/  ifm_status; } ;
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {scalar_t__ media_type; } ;
struct TYPE_6__ {TYPE_2__ mac; TYPE_1__ phy; } ;
struct adapter {int link_speed; scalar_t__ link_duplex; TYPE_3__ hw; int /*<<< orphan*/  link_active; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 scalar_t__ FULL_DUPLEX ; 
 int IFM_1000_LX ; 
 int IFM_1000_SX ; 
 int IFM_1000_T ; 
 int IFM_100_TX ; 
 int IFM_10_T ; 
 int /*<<< orphan*/  IFM_ACTIVE ; 
 int /*<<< orphan*/  IFM_AVALID ; 
 int IFM_ETHER ; 
 int IFM_FDX ; 
 int IFM_HDX ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 scalar_t__ e1000_82545 ; 
 scalar_t__ e1000_media_type_fiber ; 
 scalar_t__ e1000_media_type_internal_serdes ; 
 int /*<<< orphan*/  iflib_admin_intr_deferred (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_if_media_status(if_ctx_t ctx, struct ifmediareq *ifmr)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	u_char fiber_type = IFM_1000_SX;

	INIT_DEBUGOUT("em_if_media_status: begin");

	iflib_admin_intr_deferred(ctx);

	ifmr->ifm_status = IFM_AVALID;
	ifmr->ifm_active = IFM_ETHER;

	if (!adapter->link_active) {
		return;
	}

	ifmr->ifm_status |= IFM_ACTIVE;

	if ((adapter->hw.phy.media_type == e1000_media_type_fiber) ||
	    (adapter->hw.phy.media_type == e1000_media_type_internal_serdes)) {
		if (adapter->hw.mac.type == e1000_82545)
			fiber_type = IFM_1000_LX;
		ifmr->ifm_active |= fiber_type | IFM_FDX;
	} else {
		switch (adapter->link_speed) {
		case 10:
			ifmr->ifm_active |= IFM_10_T;
			break;
		case 100:
			ifmr->ifm_active |= IFM_100_TX;
			break;
		case 1000:
			ifmr->ifm_active |= IFM_1000_T;
			break;
		}
		if (adapter->link_duplex == FULL_DUPLEX)
			ifmr->ifm_active |= IFM_FDX;
		else
			ifmr->ifm_active |= IFM_HDX;
	}
}