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
struct TYPE_2__ {scalar_t__ hmc_obj; } ;
struct i40e_hw {TYPE_1__ hmc; } ;
struct ixl_pf {int /*<<< orphan*/  qtag; int /*<<< orphan*/  qmgr; int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
typedef  enum i40e_status_code { ____Placeholder_i40e_status_code } i40e_status_code ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int i40e_shutdown_adminq (struct i40e_hw*) ; 
 int i40e_shutdown_lan_hmc (struct i40e_hw*) ; 
 int /*<<< orphan*/  i40e_stat_str (struct i40e_hw*,int) ; 
 int /*<<< orphan*/  ixl_disable_intr0 (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ixl_teardown_hw_structs(struct ixl_pf *pf)
{
	enum i40e_status_code status = 0;
	struct i40e_hw *hw = &pf->hw;
	device_t dev = pf->dev;

	/* Shutdown LAN HMC */
	if (hw->hmc.hmc_obj) {
		status = i40e_shutdown_lan_hmc(hw);
		if (status) {
			device_printf(dev,
			    "init: LAN HMC shutdown failure; status %s\n",
			    i40e_stat_str(hw, status));
			goto err_out;
		}
	}

	/* Shutdown admin queue */
	ixl_disable_intr0(hw);
	status = i40e_shutdown_adminq(hw);
	if (status)
		device_printf(dev,
		    "init: Admin Queue shutdown failure; status %s\n",
		    i40e_stat_str(hw, status));

	ixl_pf_qmgr_release(&pf->qmgr, &pf->qtag);
err_out:
	return (status);
}