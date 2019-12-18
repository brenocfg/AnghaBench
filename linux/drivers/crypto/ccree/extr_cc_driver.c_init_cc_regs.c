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
struct device {int dummy; } ;
struct cc_drvdata {scalar_t__ hw_rev; unsigned int comp_mask; scalar_t__ coherent; } ;

/* Variables and functions */
 int /*<<< orphan*/  AXIM_CACHE_PARAMS ; 
 int /*<<< orphan*/  AXIM_CFG ; 
 unsigned int CC_AXI_ERR_IRQ_MASK ; 
 unsigned int CC_AXI_IRQ_MASK ; 
 int CC_COHERENT_CACHE_PARAMS ; 
 unsigned int CC_GPR0_IRQ_MASK ; 
 scalar_t__ CC_HW_REV_712 ; 
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_ICR ; 
 int /*<<< orphan*/  HOST_IMR ; 
 int /*<<< orphan*/  HOST_IRR ; 
 unsigned int cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,unsigned int,...) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 

int init_cc_regs(struct cc_drvdata *drvdata, bool is_probe)
{
	unsigned int val, cache_params;
	struct device *dev = drvdata_to_dev(drvdata);

	/* Unmask all AXI interrupt sources AXI_CFG1 register   */
	/* AXI interrupt config are obsoleted startign at cc7x3 */
	if (drvdata->hw_rev <= CC_HW_REV_712) {
		val = cc_ioread(drvdata, CC_REG(AXIM_CFG));
		cc_iowrite(drvdata, CC_REG(AXIM_CFG), val & ~CC_AXI_IRQ_MASK);
		dev_dbg(dev, "AXIM_CFG=0x%08X\n",
			cc_ioread(drvdata, CC_REG(AXIM_CFG)));
	}

	/* Clear all pending interrupts */
	val = cc_ioread(drvdata, CC_REG(HOST_IRR));
	dev_dbg(dev, "IRR=0x%08X\n", val);
	cc_iowrite(drvdata, CC_REG(HOST_ICR), val);

	/* Unmask relevant interrupt cause */
	val = drvdata->comp_mask | CC_AXI_ERR_IRQ_MASK;

	if (drvdata->hw_rev >= CC_HW_REV_712)
		val |= CC_GPR0_IRQ_MASK;

	cc_iowrite(drvdata, CC_REG(HOST_IMR), ~val);

	cache_params = (drvdata->coherent ? CC_COHERENT_CACHE_PARAMS : 0x0);

	val = cc_ioread(drvdata, CC_REG(AXIM_CACHE_PARAMS));

	if (is_probe)
		dev_dbg(dev, "Cache params previous: 0x%08X\n", val);

	cc_iowrite(drvdata, CC_REG(AXIM_CACHE_PARAMS), cache_params);
	val = cc_ioread(drvdata, CC_REG(AXIM_CACHE_PARAMS));

	if (is_probe)
		dev_dbg(dev, "Cache params current: 0x%08X (expect: 0x%08X)\n",
			val, cache_params);

	return 0;
}