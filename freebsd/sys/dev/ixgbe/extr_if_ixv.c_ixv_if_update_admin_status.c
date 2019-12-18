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
struct TYPE_4__ {scalar_t__ get_link_status; } ;
struct TYPE_5__ {scalar_t__ adapter_stopped; TYPE_1__ mac; } ;
struct adapter {int link_speed; scalar_t__ link_active; scalar_t__ link_up; TYPE_2__ hw; } ;
typedef  scalar_t__ s32 ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* if_init ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 scalar_t__ IXGBE_SUCCESS ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 TYPE_3__* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ixgbe_check_link (TYPE_2__*,int*,scalar_t__*,scalar_t__) ; 
 int /*<<< orphan*/  ixv_update_stats (struct adapter*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_if_update_admin_status(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	device_t       dev = iflib_get_dev(ctx);
	s32            status;

	adapter->hw.mac.get_link_status = TRUE;

	status = ixgbe_check_link(&adapter->hw, &adapter->link_speed,
	    &adapter->link_up, FALSE);

	if (status != IXGBE_SUCCESS && adapter->hw.adapter_stopped == FALSE) {
		/* Mailbox's Clear To Send status is lost or timeout occurred.
		 * We need reinitialization. */
		iflib_get_ifp(ctx)->if_init(ctx);
	}

	if (adapter->link_up) {
		if (adapter->link_active == FALSE) {
			if (bootverbose)
				device_printf(dev, "Link is up %d Gbps %s \n",
				    ((adapter->link_speed == 128) ? 10 : 1),
				    "Full Duplex");
			adapter->link_active = TRUE;
			iflib_link_state_change(ctx, LINK_STATE_UP,
			    IF_Gbps(10));
		}
	} else { /* Link down */
		if (adapter->link_active == TRUE) {
			if (bootverbose)
				device_printf(dev, "Link is Down\n");
			iflib_link_state_change(ctx, LINK_STATE_DOWN,  0);
			adapter->link_active = FALSE;
		}
	}

	/* Stats Update */
	ixv_update_stats(adapter);
}