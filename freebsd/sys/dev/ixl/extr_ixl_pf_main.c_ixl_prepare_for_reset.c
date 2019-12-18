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
struct i40e_hw {int dummy; } ;
struct ixl_pf {int /*<<< orphan*/  qtag; int /*<<< orphan*/  qmgr; int /*<<< orphan*/  dev; struct i40e_hw hw; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int i40e_shutdown_adminq (struct i40e_hw*) ; 
 int i40e_shutdown_lan_hmc (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_disable_intr0 (struct i40e_hw*) ; 
 int /*<<< orphan*/  ixl_pf_qmgr_release (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
ixl_prepare_for_reset(struct ixl_pf *pf, bool is_up)
{
	struct i40e_hw *hw = &pf->hw;
	device_t dev = pf->dev;
	int error = 0;

	error = i40e_shutdown_lan_hmc(hw);
	if (error)
		device_printf(dev,
		    "Shutdown LAN HMC failed with code %d\n", error);

	ixl_disable_intr0(hw);

	error = i40e_shutdown_adminq(hw);
	if (error)
		device_printf(dev,
		    "Shutdown Admin queue failed with code %d\n", error);

	ixl_pf_qmgr_release(&pf->qmgr, &pf->qtag);
	return (error);
}