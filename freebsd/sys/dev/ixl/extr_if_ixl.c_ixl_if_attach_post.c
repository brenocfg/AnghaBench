#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct ixl_vsi {TYPE_2__* shared; int /*<<< orphan*/  num_tx_queues; int /*<<< orphan*/  num_rx_queues; int /*<<< orphan*/  ifp; } ;
struct TYPE_10__ {int /*<<< orphan*/  num_active; int /*<<< orphan*/  num_allocated; } ;
struct TYPE_9__ {scalar_t__ iwarp; int /*<<< orphan*/  num_tx_qp; } ;
struct TYPE_8__ {int get_link_info; } ;
struct TYPE_6__ {int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_4__ func_caps; TYPE_3__ phy; TYPE_1__ aq; } ;
struct ixl_pf {int iw_enabled; scalar_t__ iw_msix; int /*<<< orphan*/  link_up; TYPE_5__ qtag; int /*<<< orphan*/  qmgr; struct i40e_hw hw; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {scalar_t__ isc_intr; int /*<<< orphan*/  isc_ntxqsets; int /*<<< orphan*/  isc_nrxqsets; } ;

/* Variables and functions */
 int EINVAL ; 
 int EIO ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 int /*<<< orphan*/  INIT_DBG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INIT_DEBUGOUT (char*,int) ; 
 int /*<<< orphan*/  IXL_DEFAULT_PHY_INT_MASK ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int i40e_aq_set_phy_int_mask (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_aq_str (struct i40e_hw*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i40e_get_link_status (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  iflib_get_dev (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_get_ifp (int /*<<< orphan*/ ) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_add_device_sysctls (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_add_hw_stats (struct ixl_pf*) ; 
 scalar_t__ ixl_attach_get_link_status (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_configure_intr0_msix (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_enable_intr0 (struct i40e_hw*) ; 
 scalar_t__ ixl_enable_iwarp ; 
 int /*<<< orphan*/  ixl_get_bus_info (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_init_filters (struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_initialize_sriov (struct ixl_pf*) ; 
 int ixl_iw_pf_attach (struct ixl_pf*) ; 
 int ixl_pf_qmgr_alloc_contiguous (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int ixl_pf_qmgr_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_pf_reset_stats (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_set_initial_advertised_speeds (struct ixl_pf*) ; 
 scalar_t__ ixl_setup_interface (int /*<<< orphan*/ ,struct ixl_pf*) ; 
 int ixl_switch_config (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_update_link_status (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_update_stats_counters (struct ixl_pf*) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ixl_if_attach_post(if_ctx_t ctx)
{
	device_t dev;
	struct ixl_pf *pf;
	struct i40e_hw *hw;
	struct ixl_vsi *vsi;
	int error = 0;
	enum i40e_status_code status;

	INIT_DBG_DEV(dev, "begin");

	dev = iflib_get_dev(ctx);
	pf = iflib_get_softc(ctx);
	vsi = &pf->vsi;
	vsi->ifp = iflib_get_ifp(ctx);
	hw = &pf->hw;

	/* Save off determined number of queues for interface */
	vsi->num_rx_queues = vsi->shared->isc_nrxqsets;
	vsi->num_tx_queues = vsi->shared->isc_ntxqsets;

	/* Setup OS network interface / ifnet */
	if (ixl_setup_interface(dev, pf)) {
		device_printf(dev, "interface setup failed!\n");
		error = EIO;
		goto err;
	}

	/* Determine link state */
	if (ixl_attach_get_link_status(pf)) {
		error = EINVAL;
		goto err;
	}

	error = ixl_switch_config(pf);
	if (error) {
		device_printf(dev, "Initial ixl_switch_config() failed: %d\n",
		     error);
		goto err;
	}

	/* Add protocol filters to list */
	ixl_init_filters(vsi);

	/* Init queue allocation manager */
	error = ixl_pf_qmgr_init(&pf->qmgr, hw->func_caps.num_tx_qp);
	if (error) {
		device_printf(dev, "Failed to init queue manager for PF queues, error %d\n",
		    error);
		goto err;
	}
	/* reserve a contiguous allocation for the PF's VSI */
	error = ixl_pf_qmgr_alloc_contiguous(&pf->qmgr,
	    max(vsi->num_rx_queues, vsi->num_tx_queues), &pf->qtag);
	if (error) {
		device_printf(dev, "Failed to reserve queues for PF LAN VSI, error %d\n",
		    error);
		goto err;
	}
	device_printf(dev, "Allocating %d queues for PF LAN VSI; %d queues active\n",
	    pf->qtag.num_allocated, pf->qtag.num_active);

	/* Limit PHY interrupts to link, autoneg, and modules failure */
	status = i40e_aq_set_phy_int_mask(hw, IXL_DEFAULT_PHY_INT_MASK,
	    NULL);
        if (status) {
		device_printf(dev, "i40e_aq_set_phy_mask() failed: err %s,"
		    " aq_err %s\n", i40e_stat_str(hw, status),
		    i40e_aq_str(hw, hw->aq.asq_last_status));
		goto err;
	}

	/* Get the bus configuration and set the shared code */
	ixl_get_bus_info(pf);

	/* Keep admin queue interrupts active while driver is loaded */
	if (vsi->shared->isc_intr == IFLIB_INTR_MSIX) {
 		ixl_configure_intr0_msix(pf);
 		ixl_enable_intr0(hw);
	}

	/* Set initial advertised speed sysctl value */
	ixl_set_initial_advertised_speeds(pf);

	/* Initialize statistics & add sysctls */
	ixl_add_device_sysctls(pf);
	ixl_pf_reset_stats(pf);
	ixl_update_stats_counters(pf);
	ixl_add_hw_stats(pf);

	hw->phy.get_link_info = true;
	i40e_get_link_status(hw, &pf->link_up);
	ixl_update_link_status(pf);

#ifdef PCI_IOV
	ixl_initialize_sriov(pf);
#endif

#ifdef IXL_IW
	if (hw->func_caps.iwarp && ixl_enable_iwarp) {
		pf->iw_enabled = (pf->iw_msix > 0) ? true : false;
		if (pf->iw_enabled) {
			error = ixl_iw_pf_attach(pf);
			if (error) {
				device_printf(dev,
				    "interfacing to iWARP driver failed: %d\n",
				    error);
				goto err;
			} else
				device_printf(dev, "iWARP ready\n");
		} else
			device_printf(dev, "iWARP disabled on this device "
			    "(no MSI-X vectors)\n");
	} else {
		pf->iw_enabled = false;
		device_printf(dev, "The device is not iWARP enabled\n");
	}
#endif

	INIT_DBG_DEV(dev, "end");
	return (0);

err:
	INIT_DEBUGOUT("end: error %d", error);
	/* ixl_if_detach() is called on error from this */
	return (error);
}