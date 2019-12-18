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
typedef  int /*<<< orphan*/  u8 ;
struct ixl_vsi {int /*<<< orphan*/  seid; scalar_t__ enable_head_writeback; TYPE_2__* shared; int /*<<< orphan*/  ifp; } ;
struct TYPE_3__ {int /*<<< orphan*/ * addr; } ;
struct i40e_hw {TYPE_1__ mac; } ;
struct ixl_pf {scalar_t__ iw_enabled; struct i40e_hw hw; struct ixl_vsi vsi; } ;
struct ifnet {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_4__ {scalar_t__ isc_intr; } ;

/* Variables and functions */
 int ETHER_ADDR_LEN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  I40E_AQC_WRITE_TYPE_LAA_ONLY ; 
 scalar_t__ I40E_SUCCESS ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/ * IF_LLADDR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_VLAN_ANY ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cmp_etheraddr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int i40e_aq_mac_address_write (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_set_default_vsi (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_check_asq_alive (struct i40e_hw*) ; 
 scalar_t__ i40e_validate_mac_addr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  if_getflags (struct ifnet*) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 struct ifnet* iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_set_mac (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ixl_add_filter (struct ixl_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_config_rss (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_configure_itr (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_configure_legacy (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_configure_queue_intr_msix (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_del_filter (struct ixl_vsi*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ixl_enable_iwarp ; 
 int /*<<< orphan*/  ixl_enable_rings (struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_if_multi_set (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_if_promisc_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_init_tx_cidx (struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_init_tx_rsqs (struct ixl_vsi*) ; 
 scalar_t__ ixl_initialize_vsi (struct ixl_vsi*) ; 
 int ixl_iw_pf_init (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_rebuild_hw_structs_after_reset (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_reconfigure_filters (struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_teardown_hw_structs (struct ixl_pf*) ; 

void
ixl_if_init(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct i40e_hw	*hw = &pf->hw;
	struct ifnet *ifp = iflib_get_ifp(ctx);
	device_t 	dev = iflib_get_dev(ctx);
	u8		tmpaddr[ETHER_ADDR_LEN];
	int		ret;

	/*
	 * If the aq is dead here, it probably means something outside of the driver
	 * did something to the adapter, like a PF reset.
	 * So, rebuild the driver's state here if that occurs.
	 */
	if (!i40e_check_asq_alive(&pf->hw)) {
		device_printf(dev, "Admin Queue is down; resetting...\n");
		ixl_teardown_hw_structs(pf);
		ixl_rebuild_hw_structs_after_reset(pf);
	}

	/* Get the latest mac address... User might use a LAA */
	bcopy(IF_LLADDR(vsi->ifp), tmpaddr, ETH_ALEN);
	if (!cmp_etheraddr(hw->mac.addr, tmpaddr) &&
	    (i40e_validate_mac_addr(tmpaddr) == I40E_SUCCESS)) {
		ixl_del_filter(vsi, hw->mac.addr, IXL_VLAN_ANY);
		bcopy(tmpaddr, hw->mac.addr, ETH_ALEN);
		ret = i40e_aq_mac_address_write(hw,
		    I40E_AQC_WRITE_TYPE_LAA_ONLY,
		    hw->mac.addr, NULL);
		if (ret) {
			device_printf(dev, "LLA address change failed!!\n");
			return;
		}
		ixl_add_filter(vsi, hw->mac.addr, IXL_VLAN_ANY);
	}

	iflib_set_mac(ctx, hw->mac.addr);

	/* Prepare the VSI: rings, hmc contexts, etc... */
	if (ixl_initialize_vsi(vsi)) {
		device_printf(dev, "initialize vsi failed!!\n");
		return;
	}
	
	/* Reconfigure multicast filters in HW */
	ixl_if_multi_set(ctx);

	/* Set up RSS */
	ixl_config_rss(pf);

	/* Set up MSI-X routing and the ITR settings */
	if (vsi->shared->isc_intr == IFLIB_INTR_MSIX) {
		ixl_configure_queue_intr_msix(pf);
		ixl_configure_itr(pf);
	} else
		ixl_configure_legacy(pf);

	if (vsi->enable_head_writeback)
		ixl_init_tx_cidx(vsi);
	else
		ixl_init_tx_rsqs(vsi);

	ixl_enable_rings(vsi);

	i40e_aq_set_default_vsi(hw, vsi->seid, NULL);

	/* Re-add configure filters to HW */
	ixl_reconfigure_filters(vsi);

	/* Configure promiscuous mode */
	ixl_if_promisc_set(ctx, if_getflags(ifp));

#ifdef IXL_IW
	if (ixl_enable_iwarp && pf->iw_enabled) {
		ret = ixl_iw_pf_init(pf);
		if (ret)
			device_printf(dev,
			    "initialize iwarp failed, code %d\n", ret);
	}
#endif
}