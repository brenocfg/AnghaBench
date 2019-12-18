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
struct TYPE_7__ {scalar_t__ (* set_vfta ) (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {TYPE_3__ ops; } ;
struct ixgbe_hw {TYPE_4__ mac; } ;
struct ifnet {int if_capenable; } ;
struct adapter {scalar_t__ num_vlans; int num_rx_queues; TYPE_2__* rx_queues; struct ixgbe_hw hw; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/  vtag_strip; } ;
struct TYPE_6__ {TYPE_1__ rxr; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int IFCAP_VLAN_HWFILTER ; 
 int IFCAP_VLAN_HWTAGGING ; 
 int IXGBE_READ_REG (struct ixgbe_hw*,int /*<<< orphan*/ ) ; 
 int IXGBE_RXDCTL_VME ; 
 int /*<<< orphan*/  IXGBE_VFRXDCTL (int) ; 
 int IXGBE_VFTA_SIZE ; 
 int /*<<< orphan*/  IXGBE_WRITE_REG (struct ixgbe_hw*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRUE ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct adapter* iflib_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__* ixv_shadow_vfta ; 
 scalar_t__ stub1 (struct ixgbe_hw*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixv_setup_vlan_support(if_ctx_t ctx)
{
	struct ifnet	*ifp = iflib_get_ifp(ctx);
	struct adapter  *adapter = iflib_get_softc(ctx);
	struct ixgbe_hw *hw = &adapter->hw;
	u32             ctrl, vid, vfta, retry;

	/*
	 * We get here thru if_init, meaning
	 * a soft reset, this has already cleared
	 * the VFTA and other state, so if there
	 * have been no vlan's registered do nothing.
	 */
	if (adapter->num_vlans == 0)
		return;

	if (ifp->if_capenable & IFCAP_VLAN_HWTAGGING) {
		/* Enable the queues */
		for (int i = 0; i < adapter->num_rx_queues; i++) {
			ctrl = IXGBE_READ_REG(hw, IXGBE_VFRXDCTL(i));
			ctrl |= IXGBE_RXDCTL_VME;
			IXGBE_WRITE_REG(hw, IXGBE_VFRXDCTL(i), ctrl);
			/*
			 * Let Rx path know that it needs to store VLAN tag
			 * as part of extra mbuf info.
			 */
			adapter->rx_queues[i].rxr.vtag_strip = TRUE;
		}
	}

	/*
	 * If filtering VLAN tags is disabled,
	 * there is no need to fill VLAN Filter Table Array (VFTA).
	 */
	if ((ifp->if_capenable & IFCAP_VLAN_HWFILTER) == 0)
		return;

	/*
	 * A soft reset zero's out the VFTA, so
	 * we need to repopulate it now.
	 */
	for (int i = 0; i < IXGBE_VFTA_SIZE; i++) {
		if (ixv_shadow_vfta[i] == 0)
			continue;
		vfta = ixv_shadow_vfta[i];
		/*
		 * Reconstruct the vlan id's
		 * based on the bits set in each
		 * of the array ints.
		 */
		for (int j = 0; j < 32; j++) {
			retry = 0;
			if ((vfta & (1 << j)) == 0)
				continue;
			vid = (i * 32) + j;
			/* Call the shared code mailbox routine */
			while (hw->mac.ops.set_vfta(hw, vid, 0, TRUE, FALSE)) {
				if (++retry > 5)
					break;
			}
		}
	}
}