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
struct TYPE_4__ {int /*<<< orphan*/  get_link_info; } ;
struct TYPE_3__ {int fw_maj_ver; int fw_min_ver; int /*<<< orphan*/  asq_last_status; } ;
struct i40e_hw {TYPE_2__ phy; TYPE_1__ aq; } ;
struct ixl_pf {int /*<<< orphan*/  link_up; struct i40e_hw hw; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int i40e_aq_set_link_restart_an (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_get_link_status (struct i40e_hw*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i40e_msec_delay (int) ; 

int
ixl_attach_get_link_status(struct ixl_pf *pf)
{
	struct i40e_hw *hw = &pf->hw;
	device_t dev = pf->dev;
	int error = 0;

	if (((hw->aq.fw_maj_ver == 4) && (hw->aq.fw_min_ver < 33)) ||
	    (hw->aq.fw_maj_ver < 4)) {
		i40e_msec_delay(75);
		error = i40e_aq_set_link_restart_an(hw, TRUE, NULL);
		if (error) {
			device_printf(dev, "link restart failed, aq_err=%d\n",
			    pf->hw.aq.asq_last_status);
			return error;
		}
	}

	/* Determine link state */
	hw->phy.get_link_info = TRUE;
	i40e_get_link_status(hw, &pf->link_up);
	return (0);
}