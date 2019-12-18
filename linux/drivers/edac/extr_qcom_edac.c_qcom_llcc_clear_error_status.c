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
struct llcc_drv_data {int /*<<< orphan*/  bcast_regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRP_ECC_ERROR_CNTR_CLEAR ; 
 int /*<<< orphan*/  DRP_INTERRUPT_CLEAR ; 
 int /*<<< orphan*/  DRP_TRP_CNT_CLEAR ; 
 int /*<<< orphan*/  DRP_TRP_INT_CLEAR ; 
 int /*<<< orphan*/  EDAC_LLCC ; 
 int EINVAL ; 
 int /*<<< orphan*/  KERN_CRIT ; 
#define  LLCC_DRAM_CE 131 
#define  LLCC_DRAM_UE 130 
#define  LLCC_TRAM_CE 129 
#define  LLCC_TRAM_UE 128 
 int /*<<< orphan*/  TRP_ECC_ERROR_CNTR_CLEAR ; 
 int /*<<< orphan*/  TRP_INTERRUPT_0_CLEAR ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
qcom_llcc_clear_error_status(int err_type, struct llcc_drv_data *drv)
{
	int ret = 0;

	switch (err_type) {
	case LLCC_DRAM_CE:
	case LLCC_DRAM_UE:
		ret = regmap_write(drv->bcast_regmap, DRP_INTERRUPT_CLEAR,
				   DRP_TRP_INT_CLEAR);
		if (ret)
			return ret;

		ret = regmap_write(drv->bcast_regmap, DRP_ECC_ERROR_CNTR_CLEAR,
				   DRP_TRP_CNT_CLEAR);
		if (ret)
			return ret;
		break;
	case LLCC_TRAM_CE:
	case LLCC_TRAM_UE:
		ret = regmap_write(drv->bcast_regmap, TRP_INTERRUPT_0_CLEAR,
				   DRP_TRP_INT_CLEAR);
		if (ret)
			return ret;

		ret = regmap_write(drv->bcast_regmap, TRP_ECC_ERROR_CNTR_CLEAR,
				   DRP_TRP_CNT_CLEAR);
		if (ret)
			return ret;
		break;
	default:
		ret = -EINVAL;
		edac_printk(KERN_CRIT, EDAC_LLCC, "Unexpected error type: %d\n",
			    err_type);
	}
	return ret;
}