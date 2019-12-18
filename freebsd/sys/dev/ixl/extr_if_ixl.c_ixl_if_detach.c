#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ixl_vsi {int /*<<< orphan*/  media; } ;
struct TYPE_2__ {scalar_t__ hmc_obj; } ;
struct i40e_hw {TYPE_1__ hmc; } ;
struct ixl_pf {int /*<<< orphan*/  qmgr; scalar_t__ iw_enabled; int /*<<< orphan*/  dev; struct i40e_hw hw; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  INIT_DBG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 
 int i40e_shutdown_adminq (struct i40e_hw*) ; 
 int i40e_shutdown_lan_hmc (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_disable_intr0 (struct i40e_hw*) ; 
 scalar_t__ ixl_enable_iwarp ; 
 int /*<<< orphan*/  ixl_free_mac_filters (struct ixl_vsi*) ; 
 int /*<<< orphan*/  ixl_free_pci_resources (struct ixl_pf*) ; 
 int ixl_iw_pf_detach (struct ixl_pf*) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ixl_if_detach(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct i40e_hw *hw = &pf->hw;
	device_t dev = pf->dev;
	enum i40e_status_code	status;
#ifdef IXL_IW
	int			error;
#endif

	INIT_DBG_DEV(dev, "begin");

#ifdef IXL_IW
	if (ixl_enable_iwarp && pf->iw_enabled) {
		error = ixl_iw_pf_detach(pf);
		if (error == EBUSY) {
			device_printf(dev, "iwarp in use; stop it first.\n");
			//return (error);
		}
	}
#endif
	/* Remove all previously allocated media types */
	ifmedia_removeall(vsi->media);

	/* Shutdown LAN HMC */
	if (hw->hmc.hmc_obj) {
		status = i40e_shutdown_lan_hmc(hw);
		if (status)
			device_printf(dev,
			    "i40e_shutdown_lan_hmc() failed with status %s\n",
			    i40e_stat_str(hw, status));
	}

	/* Shutdown admin queue */
	ixl_disable_intr0(hw);
	status = i40e_shutdown_adminq(hw);
	if (status)
		device_printf(dev,
		    "i40e_shutdown_adminq() failed with status %s\n",
		    i40e_stat_str(hw, status));

	ixl_pf_qmgr_destroy(&pf->qmgr);
	ixl_free_pci_resources(pf);
	ixl_free_mac_filters(vsi);
	INIT_DBG_DEV(dev, "end");
	return (0);
}