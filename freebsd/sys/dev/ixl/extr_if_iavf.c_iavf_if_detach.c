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
struct ixl_vsi {int /*<<< orphan*/  media; } ;
struct i40e_hw {int dummy; } ;
struct iavf_sc {int /*<<< orphan*/  vf_res; struct i40e_hw hw; int /*<<< orphan*/  dev; struct ixl_vsi vsi; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int I40E_SUCCESS ; 
 int /*<<< orphan*/  INIT_DBG_DEV (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  M_IAVF ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int i40e_shutdown_adminq (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  iavf_disable_adminq_irq (struct i40e_hw*) ; 
 int /*<<< orphan*/  iavf_free_filters (struct iavf_sc*) ; 
 int /*<<< orphan*/  iavf_free_pci_resources (struct iavf_sc*) ; 
 struct iavf_sc* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iavf_if_detach(if_ctx_t ctx)
{
	struct iavf_sc *sc = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &sc->vsi;
	struct i40e_hw *hw = &sc->hw;
	device_t dev = sc->dev;
	enum i40e_status_code status;

	INIT_DBG_DEV(dev, "begin");

	/* Remove all the media and link information */
	ifmedia_removeall(vsi->media);

	iavf_disable_adminq_irq(hw);
	status = i40e_shutdown_adminq(&sc->hw);
	if (status != I40E_SUCCESS) {
		device_printf(dev,
		    "i40e_shutdown_adminq() failed with status %s\n",
		    i40e_stat_str(hw, status));
	}

	free(sc->vf_res, M_IAVF);
	iavf_free_pci_resources(sc);
	iavf_free_filters(sc);

	INIT_DBG_DEV(dev, "end");
	return (0);
}