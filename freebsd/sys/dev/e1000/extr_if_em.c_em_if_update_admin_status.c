#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_8__ {scalar_t__ type; int serdes_has_link; int /*<<< orphan*/  addr; int /*<<< orphan*/  get_link_status; } ;
struct TYPE_6__ {int media_changed; } ;
struct TYPE_7__ {TYPE_2__ _82575; } ;
struct TYPE_5__ {int media_type; scalar_t__ id; } ;
struct e1000_hw {TYPE_4__ mac; TYPE_3__ dev_spec; TYPE_1__ phy; } ;
struct adapter {int link_active; scalar_t__ link_speed; scalar_t__ link_duplex; scalar_t__ intr_type; struct e1000_hw hw; int /*<<< orphan*/  flags; scalar_t__ smartspeed; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  E1000_CTRL_EXT ; 
 int E1000_CTRL_EXT_LINK_MODE_GMII ; 
 int E1000_CTRL_EXT_LINK_MODE_MASK ; 
 int /*<<< orphan*/  E1000_IMS ; 
 int E1000_IMS_LSC ; 
 int E1000_READ_REG (struct e1000_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_STATUS ; 
 int E1000_STATUS_LU ; 
 int /*<<< orphan*/  E1000_TARC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E1000_THSTAT ; 
 int E1000_THSTAT_LINK_THROTTLE ; 
 int /*<<< orphan*/  E1000_WRITE_REG (struct e1000_hw*,int /*<<< orphan*/ ,int) ; 
 int EM_MSIX_LINK ; 
 scalar_t__ FULL_DUPLEX ; 
 scalar_t__ I210_I_PHY_ID ; 
 int I210_LINK_DELAY ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  IF_Mbps (scalar_t__) ; 
 int /*<<< orphan*/  IGB_MEDIA_RESET ; 
 int /*<<< orphan*/  LINK_STATE_DOWN ; 
 int /*<<< orphan*/  LINK_STATE_UP ; 
 scalar_t__ SPEED_1000 ; 
 int TARC_SPEED_MODE_BIT ; 
 int TRUE ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ e1000_82571 ; 
 scalar_t__ e1000_82572 ; 
 scalar_t__ e1000_82574 ; 
 int /*<<< orphan*/  e1000_cfg_on_link_up (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_check_for_link (struct e1000_hw*) ; 
 scalar_t__ e1000_get_laa_state_82571 (struct e1000_hw*) ; 
 int /*<<< orphan*/  e1000_get_speed_and_duplex (struct e1000_hw*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ e1000_i210 ; 
 scalar_t__ e1000_i211 ; 
 scalar_t__ e1000_i350 ; 
#define  e1000_media_type_copper 131 
#define  e1000_media_type_fiber 130 
#define  e1000_media_type_internal_serdes 129 
#define  e1000_media_type_unknown 128 
 scalar_t__ e1000_pch_spt ; 
 int /*<<< orphan*/  e1000_rar_set (struct e1000_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ em_mac_min ; 
 int /*<<< orphan*/  em_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  em_update_stats_counters (struct adapter*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_link_state_change (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ igb_mac_min ; 
 int /*<<< orphan*/  lem_smartspeed (struct adapter*) ; 
 int /*<<< orphan*/  msec_delay (int) ; 

__attribute__((used)) static void
em_if_update_admin_status(if_ctx_t ctx)
{
	struct adapter *adapter = iflib_get_softc(ctx);
	struct e1000_hw *hw = &adapter->hw;
	device_t dev = iflib_get_dev(ctx);
	u32 link_check, thstat, ctrl;

	link_check = thstat = ctrl = 0;
	/* Get the cached link value or read phy for real */
	switch (hw->phy.media_type) {
	case e1000_media_type_copper:
		if (hw->mac.get_link_status) {
			if (hw->mac.type == e1000_pch_spt)
				msec_delay(50);
			/* Do the work to read phy */
			e1000_check_for_link(hw);
			link_check = !hw->mac.get_link_status;
			if (link_check) /* ESB2 fix */
				e1000_cfg_on_link_up(hw);
		} else {
			link_check = TRUE;
		}
		break;
	case e1000_media_type_fiber:
		e1000_check_for_link(hw);
		link_check = (E1000_READ_REG(hw, E1000_STATUS) &
			    E1000_STATUS_LU);
		break;
	case e1000_media_type_internal_serdes:
		e1000_check_for_link(hw);
		link_check = adapter->hw.mac.serdes_has_link;
		break;
	/* VF device is type_unknown */
	case e1000_media_type_unknown:
		e1000_check_for_link(hw);
		link_check = !hw->mac.get_link_status;
		/* FALLTHROUGH */
	default:
		break;
	}

	/* Check for thermal downshift or shutdown */
	if (hw->mac.type == e1000_i350) {
		thstat = E1000_READ_REG(hw, E1000_THSTAT);
		ctrl = E1000_READ_REG(hw, E1000_CTRL_EXT);
	}

	/* Now check for a transition */
	if (link_check && (adapter->link_active == 0)) {
		e1000_get_speed_and_duplex(hw, &adapter->link_speed,
		    &adapter->link_duplex);
		/* Check if we must disable SPEED_MODE bit on PCI-E */
		if ((adapter->link_speed != SPEED_1000) &&
		    ((hw->mac.type == e1000_82571) ||
		    (hw->mac.type == e1000_82572))) {
			int tarc0;
			tarc0 = E1000_READ_REG(hw, E1000_TARC(0));
			tarc0 &= ~TARC_SPEED_MODE_BIT;
			E1000_WRITE_REG(hw, E1000_TARC(0), tarc0);
		}
		if (bootverbose)
			device_printf(dev, "Link is up %d Mbps %s\n",
			    adapter->link_speed,
			    ((adapter->link_duplex == FULL_DUPLEX) ?
			    "Full Duplex" : "Half Duplex"));
		adapter->link_active = 1;
		adapter->smartspeed = 0;
		if ((ctrl & E1000_CTRL_EXT_LINK_MODE_MASK) ==
		    E1000_CTRL_EXT_LINK_MODE_GMII &&
		    (thstat & E1000_THSTAT_LINK_THROTTLE))
			device_printf(dev, "Link: thermal downshift\n");
		/* Delay Link Up for Phy update */
		if (((hw->mac.type == e1000_i210) ||
		    (hw->mac.type == e1000_i211)) &&
		    (hw->phy.id == I210_I_PHY_ID))
			msec_delay(I210_LINK_DELAY);
		/* Reset if the media type changed. */
		if ((hw->dev_spec._82575.media_changed) &&
			(adapter->hw.mac.type >= igb_mac_min)) {
			hw->dev_spec._82575.media_changed = false;
			adapter->flags |= IGB_MEDIA_RESET;
			em_reset(ctx);
		}
		iflib_link_state_change(ctx, LINK_STATE_UP,
		    IF_Mbps(adapter->link_speed));
	} else if (!link_check && (adapter->link_active == 1)) {
		adapter->link_speed = 0;
		adapter->link_duplex = 0;
		adapter->link_active = 0;
		iflib_link_state_change(ctx, LINK_STATE_DOWN, 0);
	}
	em_update_stats_counters(adapter);

	/* Reset LAA into RAR[0] on 82571 */
	if (hw->mac.type == e1000_82571 && e1000_get_laa_state_82571(hw))
		e1000_rar_set(hw, hw->mac.addr, 0);

	if (hw->mac.type < em_mac_min)
		lem_smartspeed(adapter);
	else if (hw->mac.type == e1000_82574 &&
	    adapter->intr_type == IFLIB_INTR_MSIX)
		E1000_WRITE_REG(&adapter->hw, E1000_IMS, EM_MSIX_LINK |
		    E1000_IMS_LSC);
}