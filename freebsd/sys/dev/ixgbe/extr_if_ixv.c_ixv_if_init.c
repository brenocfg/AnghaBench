#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* check_link ) (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* start_hw ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* reset_hw ) (struct ixgbe_hw*) ;int /*<<< orphan*/  (* set_rar ) (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  (* stop_adapter ) (struct ixgbe_hw*) ;} ;
struct TYPE_4__ {TYPE_1__ ops; int /*<<< orphan*/  addr; } ;
struct ixgbe_hw {TYPE_2__ mac; int /*<<< orphan*/  adapter_stopped; } ;
struct ifnet {int dummy; } ;
struct adapter {int /*<<< orphan*/  link_up; int /*<<< orphan*/  link_speed; int /*<<< orphan*/  vector; int /*<<< orphan*/  rx_mbuf_sz; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IF_LLADDR (struct ifnet*) ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*) ; 
 int /*<<< orphan*/  IXGBE_EICS_RTX_QUEUE ; 
 int /*<<< orphan*/  IXGBE_ETH_LENGTH_OF_ADDRESS ; 
 int /*<<< orphan*/  IXGBE_LINK_ITR ; 
 int IXGBE_RAH_AV ; 
 int /*<<< orphan*/  IXGBE_VTEIAM ; 
 int /*<<< orphan*/  IXGBE_VTEITR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_rx_mbuf_sz (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixv_configure_ivars (struct adapter*) ; 
 int /*<<< orphan*/  ixv_if_enable_intr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixv_if_multi_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixv_init_stats (struct adapter*) ; 
 int /*<<< orphan*/  ixv_initialize_receive_units (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixv_initialize_transmit_units (int /*<<< orphan*/ ) ; 
 int ixv_negotiate_api (struct adapter*) ; 
 int /*<<< orphan*/  ixv_setup_vlan_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub2 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct ixgbe_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub5 (struct ixgbe_hw*) ; 
 int /*<<< orphan*/  stub6 (struct ixgbe_hw*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_if_init(if_ctx_t ctx)
{
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ifnet    *ifp = iflib_get_ifp(ctx);
	device_t        dev = iflib_get_dev(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	int             error = 0;

	INIT_DEBUGOUT("ixv_if_init: begin");
	hw->adapter_stopped = FALSE;
	hw->mac.ops.stop_adapter(hw);

	/* reprogram the RAR[0] in case user changed it. */
	hw->mac.ops.set_rar(hw, 0, hw->mac.addr, 0, IXGBE_RAH_AV);

	/* Get the latest mac address, User can use a LAA */
	bcopy(IF_LLADDR(ifp), hw->mac.addr, IXGBE_ETH_LENGTH_OF_ADDRESS);
	hw->mac.ops.set_rar(hw, 0, hw->mac.addr, 0, 1);

	/* Reset VF and renegotiate mailbox API version */
	hw->mac.ops.reset_hw(hw);
	hw->mac.ops.start_hw(hw);
	error = ixv_negotiate_api(adapter);
	if (error) {
		device_printf(dev,
		    "Mailbox API negotiation failed in if_init!\n");
		return;
	}

	ixv_initialize_transmit_units(ctx);

	/* Setup Multicast table */
	ixv_if_multi_set(ctx);

	adapter->rx_mbuf_sz = iflib_get_rx_mbuf_sz(ctx);

	/* Configure RX settings */
	ixv_initialize_receive_units(ctx);

	/* Set up VLAN offload and filter */
	ixv_setup_vlan_support(ctx);

	/* Set up MSI-X routing */
	ixv_configure_ivars(adapter);

	/* Set up auto-mask */
	IXGBE_WRITE_REG(hw, IXGBE_VTEIAM, IXGBE_EICS_RTX_QUEUE);

	/* Set moderation on the Link interrupt */
	IXGBE_WRITE_REG(hw, IXGBE_VTEITR(adapter->vector), IXGBE_LINK_ITR);

	/* Stats init */
	ixv_init_stats(adapter);

	/* Config/Enable Link */
	hw->mac.ops.check_link(hw, &adapter->link_speed, &adapter->link_up,
	    FALSE);

	/* And now turn on interrupts */
	ixv_if_enable_intr(ctx);

	return;
}