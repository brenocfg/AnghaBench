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
typedef  int /*<<< orphan*/  u32 ;
struct llcc_drv_data {int dummy; } ;
struct edac_device_ctl_info {struct llcc_drv_data* pvt_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDAC_LLCC ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_CRIT ; 
#define  LLCC_DRAM_CE 131 
#define  LLCC_DRAM_UE 130 
#define  LLCC_TRAM_CE 129 
#define  LLCC_TRAM_UE 128 
 int dump_syn_reg_values (struct llcc_drv_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  edac_device_handle_ce (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_device_handle_ue (struct edac_device_ctl_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int
dump_syn_reg(struct edac_device_ctl_info *edev_ctl, int err_type, u32 bank)
{
	struct llcc_drv_data *drv = edev_ctl->pvt_info;
	int ret;

	ret = dump_syn_reg_values(drv, bank, err_type);
	if (ret)
		return ret;

	switch (err_type) {
	case LLCC_DRAM_CE:
		edac_device_handle_ce(edev_ctl, 0, bank,
				      "LLCC Data RAM correctable Error");
		break;
	case LLCC_DRAM_UE:
		edac_device_handle_ue(edev_ctl, 0, bank,
				      "LLCC Data RAM uncorrectable Error");
		break;
	case LLCC_TRAM_CE:
		edac_device_handle_ce(edev_ctl, 0, bank,
				      "LLCC Tag RAM correctable Error");
		break;
	case LLCC_TRAM_UE:
		edac_device_handle_ue(edev_ctl, 0, bank,
				      "LLCC Tag RAM uncorrectable Error");
		break;
	default:
		ret = -EINVAL;
		edac_printk(KERN_CRIT, EDAC_LLCC, "Unexpected error type: %d\n",
			    err_type);
	}

	return ret;
}