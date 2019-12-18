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
typedef  int u32 ;
struct device {int dummy; } ;
struct cc_drvdata {int irq; int comp_mask; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  AXIM_MON_ERR ; 
 int CC_AXI_ERR_IRQ_MASK ; 
 int CC_GPR0_IRQ_MASK ; 
 int /*<<< orphan*/  CC_REG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOST_ICR ; 
 int /*<<< orphan*/  HOST_IMR ; 
 int /*<<< orphan*/  HOST_IRR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int cc_ioread (struct cc_drvdata*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cc_iowrite (struct cc_drvdata*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ cc_pm_is_dev_suspended (struct device*) ; 
 int /*<<< orphan*/  complete_request (struct cc_drvdata*) ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int) ; 
 int /*<<< orphan*/  dev_dbg_ratelimited (struct device*,char*,int) ; 
 struct device* drvdata_to_dev (struct cc_drvdata*) ; 
 int /*<<< orphan*/  fips_handler (struct cc_drvdata*) ; 

__attribute__((used)) static irqreturn_t cc_isr(int irq, void *dev_id)
{
	struct cc_drvdata *drvdata = (struct cc_drvdata *)dev_id;
	struct device *dev = drvdata_to_dev(drvdata);
	u32 irr;
	u32 imr;

	/* STAT_OP_TYPE_GENERIC STAT_PHASE_0: Interrupt */
	/* if driver suspended return, probebly shared interrupt */
	if (cc_pm_is_dev_suspended(dev))
		return IRQ_NONE;

	/* read the interrupt status */
	irr = cc_ioread(drvdata, CC_REG(HOST_IRR));
	dev_dbg(dev, "Got IRR=0x%08X\n", irr);

	if (irr == 0) /* Probably shared interrupt line */
		return IRQ_NONE;

	imr = cc_ioread(drvdata, CC_REG(HOST_IMR));

	/* clear interrupt - must be before processing events */
	cc_iowrite(drvdata, CC_REG(HOST_ICR), irr);

	drvdata->irq = irr;
	/* Completion interrupt - most probable */
	if (irr & drvdata->comp_mask) {
		/* Mask all completion interrupts - will be unmasked in
		 * deferred service handler
		 */
		cc_iowrite(drvdata, CC_REG(HOST_IMR), imr | drvdata->comp_mask);
		irr &= ~drvdata->comp_mask;
		complete_request(drvdata);
	}
#ifdef CONFIG_CRYPTO_FIPS
	/* TEE FIPS interrupt */
	if (irr & CC_GPR0_IRQ_MASK) {
		/* Mask interrupt - will be unmasked in Deferred service
		 * handler
		 */
		cc_iowrite(drvdata, CC_REG(HOST_IMR), imr | CC_GPR0_IRQ_MASK);
		irr &= ~CC_GPR0_IRQ_MASK;
		fips_handler(drvdata);
	}
#endif
	/* AXI error interrupt */
	if (irr & CC_AXI_ERR_IRQ_MASK) {
		u32 axi_err;

		/* Read the AXI error ID */
		axi_err = cc_ioread(drvdata, CC_REG(AXIM_MON_ERR));
		dev_dbg(dev, "AXI completion error: axim_mon_err=0x%08X\n",
			axi_err);

		irr &= ~CC_AXI_ERR_IRQ_MASK;
	}

	if (irr) {
		dev_dbg_ratelimited(dev, "IRR includes unknown cause bits (0x%08X)\n",
				    irr);
		/* Just warning */
	}

	return IRQ_HANDLED;
}