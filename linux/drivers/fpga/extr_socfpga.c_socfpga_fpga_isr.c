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
struct socfpga_fpga_priv {int /*<<< orphan*/  status_complete; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_EXT_PORTA_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INTEN_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_INTSTAT_OFST ; 
 int /*<<< orphan*/  SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST ; 
 int SOCFPGA_FPGMGR_MON_CONF_DONE ; 
 int SOCFPGA_FPGMGR_MON_NSTATUS ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int socfpga_fpga_raw_readl (struct socfpga_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socfpga_fpga_raw_writel (struct socfpga_fpga_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static irqreturn_t socfpga_fpga_isr(int irq, void *dev_id)
{
	struct socfpga_fpga_priv *priv = dev_id;
	u32 irqs, st;
	bool conf_done, nstatus;

	/* clear irqs */
	irqs = socfpga_fpga_raw_readl(priv, SOCFPGA_FPGMGR_GPIO_INTSTAT_OFST);

	socfpga_fpga_raw_writel(priv, SOCFPGA_FPGMGR_GPIO_PORTA_EOI_OFST, irqs);

	st = socfpga_fpga_raw_readl(priv, SOCFPGA_FPGMGR_GPIO_EXT_PORTA_OFST);
	conf_done = (st & SOCFPGA_FPGMGR_MON_CONF_DONE) != 0;
	nstatus = (st & SOCFPGA_FPGMGR_MON_NSTATUS) != 0;

	/* success */
	if (conf_done && nstatus) {
		/* disable irqs */
		socfpga_fpga_raw_writel(priv,
					SOCFPGA_FPGMGR_GPIO_INTEN_OFST, 0);
		complete(&priv->status_complete);
	}

	return IRQ_HANDLED;
}