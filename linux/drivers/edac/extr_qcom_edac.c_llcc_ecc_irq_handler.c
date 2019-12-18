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
typedef  size_t u32 ;
struct llcc_drv_data {size_t num_banks; scalar_t__* offsets; int /*<<< orphan*/  regmap; } ;
struct edac_device_ctl_info {struct llcc_drv_data* pvt_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 size_t DB_ECC_ERROR ; 
 scalar_t__ DRP_INTERRUPT_STATUS ; 
 int /*<<< orphan*/  EDAC_LLCC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  KERN_CRIT ; 
 int /*<<< orphan*/  LLCC_DRAM_CE ; 
 int /*<<< orphan*/  LLCC_DRAM_UE ; 
 int /*<<< orphan*/  LLCC_TRAM_CE ; 
 int /*<<< orphan*/  LLCC_TRAM_UE ; 
 size_t SB_ECC_ERROR ; 
 scalar_t__ TRP_INTERRUPT_0_STATUS ; 
 int dump_syn_reg (void*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  edac_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int regmap_read (int /*<<< orphan*/ ,scalar_t__,size_t*) ; 

__attribute__((used)) static irqreturn_t
llcc_ecc_irq_handler(int irq, void *edev_ctl)
{
	struct edac_device_ctl_info *edac_dev_ctl = edev_ctl;
	struct llcc_drv_data *drv = edac_dev_ctl->pvt_info;
	irqreturn_t irq_rc = IRQ_NONE;
	u32 drp_error, trp_error, i;
	int ret;

	/* Iterate over the banks and look for Tag RAM or Data RAM errors */
	for (i = 0; i < drv->num_banks; i++) {
		ret = regmap_read(drv->regmap,
				  drv->offsets[i] + DRP_INTERRUPT_STATUS,
				  &drp_error);

		if (!ret && (drp_error & SB_ECC_ERROR)) {
			edac_printk(KERN_CRIT, EDAC_LLCC,
				    "Single Bit Error detected in Data RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_DRAM_CE, i);
		} else if (!ret && (drp_error & DB_ECC_ERROR)) {
			edac_printk(KERN_CRIT, EDAC_LLCC,
				    "Double Bit Error detected in Data RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_DRAM_UE, i);
		}
		if (!ret)
			irq_rc = IRQ_HANDLED;

		ret = regmap_read(drv->regmap,
				  drv->offsets[i] + TRP_INTERRUPT_0_STATUS,
				  &trp_error);

		if (!ret && (trp_error & SB_ECC_ERROR)) {
			edac_printk(KERN_CRIT, EDAC_LLCC,
				    "Single Bit Error detected in Tag RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_TRAM_CE, i);
		} else if (!ret && (trp_error & DB_ECC_ERROR)) {
			edac_printk(KERN_CRIT, EDAC_LLCC,
				    "Double Bit Error detected in Tag RAM\n");
			ret = dump_syn_reg(edev_ctl, LLCC_TRAM_UE, i);
		}
		if (!ret)
			irq_rc = IRQ_HANDLED;
	}

	return irq_rc;
}