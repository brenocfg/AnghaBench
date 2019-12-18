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
struct adapter {scalar_t__ link_active; int link_speed; int feat_en; int task_requests; int /*<<< orphan*/  hw; scalar_t__ link_up; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IF_Gbps (int) ; 
 int IXGBE_FEATURE_SRIOV ; 
 int IXGBE_REQUEST_TASK_FDIR ; 
 int IXGBE_REQUEST_TASK_MBX ; 
 int IXGBE_REQUEST_TASK_MOD ; 
 int IXGBE_REQUEST_TASK_MSF ; 
 int IXGBE_REQUEST_TASK_PHY ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_config_dmac (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_fc_enable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixgbe_handle_mbx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_handle_mod (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_handle_msf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_handle_phy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_ping_all_vfs (struct adapter*) ; 
 int /*<<< orphan*/  ixgbe_reinit_fdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixgbe_update_stats_counters (struct adapter*) ; 

__attribute__((used)) static void
ixgbe_if_update_admin_status(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	device_t       dev = iflib_get_dev(ctx);

	if (adapter->link_up) {
		if (adapter->link_active == FALSE) {
			if (bootverbose)
				device_printf(dev, "Link is up %d Gbps %s \n",
				    ((adapter->link_speed == 128) ? 10 : 1),
				    "Full Duplex");
			adapter->link_active = TRUE;
			/* Update any Flow Control changes */
			ixgbe_fc_enable(&adapter->hw);
			/* Update DMA coalescing config */
			ixgbe_config_dmac(adapter);
			/* should actually be negotiated value */
			iflib_link_state_change(ctx, LINK_STATE_UP, IF_Gbps(10));

			if (adapter->feat_en & IXGBE_FEATURE_SRIOV)
				ixgbe_ping_all_vfs(adapter);
		}
	} else { /* Link down */
		if (adapter->link_active == TRUE) {
			if (bootverbose)
				device_printf(dev, "Link is Down\n");
			iflib_link_state_change(ctx, LINK_STATE_DOWN, 0);
			adapter->link_active = FALSE;
			if (adapter->feat_en & IXGBE_FEATURE_SRIOV)
				ixgbe_ping_all_vfs(adapter);
		}
	}

	/* Handle task requests from msix_link() */
	if (adapter->task_requests & IXGBE_REQUEST_TASK_MOD)
		ixgbe_handle_mod(ctx);
	if (adapter->task_requests & IXGBE_REQUEST_TASK_MSF)
		ixgbe_handle_msf(ctx);
	if (adapter->task_requests & IXGBE_REQUEST_TASK_MBX)
		ixgbe_handle_mbx(ctx);
	if (adapter->task_requests & IXGBE_REQUEST_TASK_FDIR)
		ixgbe_reinit_fdir(ctx);
	if (adapter->task_requests & IXGBE_REQUEST_TASK_PHY)
		ixgbe_handle_phy(ctx);
	adapter->task_requests = 0;

	ixgbe_update_stats_counters(adapter);
}