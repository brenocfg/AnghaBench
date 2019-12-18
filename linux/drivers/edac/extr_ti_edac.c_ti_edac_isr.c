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
struct ti_edac {int dummy; } ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; struct ti_edac* pvt_info; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int EMIF_1B_ECC_ERR ; 
 int /*<<< orphan*/  EMIF_1B_ECC_ERR_ADDR_LOG ; 
 int /*<<< orphan*/  EMIF_1B_ECC_ERR_CNT ; 
 int EMIF_2B_ECC_ERR ; 
 int /*<<< orphan*/  EMIF_2B_ECC_ERR_ADDR_LOG ; 
 int /*<<< orphan*/  EMIF_IRQ_STATUS ; 
 int EMIF_WR_ECC_ERR ; 
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int ti_edac_readl (struct ti_edac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_edac_writel (struct ti_edac*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t ti_edac_isr(int irq, void *data)
{
	struct mem_ctl_info *mci = data;
	struct ti_edac *edac = mci->pvt_info;
	u32 irq_status;
	u32 err_addr;
	int err_count;

	irq_status = ti_edac_readl(edac, EMIF_IRQ_STATUS);

	if (irq_status & EMIF_1B_ECC_ERR) {
		err_addr = ti_edac_readl(edac, EMIF_1B_ECC_ERR_ADDR_LOG);
		err_count = ti_edac_readl(edac, EMIF_1B_ECC_ERR_CNT);
		ti_edac_writel(edac, err_count, EMIF_1B_ECC_ERR_CNT);
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci, err_count,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, -1, 0, 0, 0,
				     mci->ctl_name, "1B");
	}

	if (irq_status & EMIF_2B_ECC_ERR) {
		err_addr = ti_edac_readl(edac, EMIF_2B_ECC_ERR_ADDR_LOG);
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     err_addr >> PAGE_SHIFT,
				     err_addr & ~PAGE_MASK, -1, 0, 0, 0,
				     mci->ctl_name, "2B");
	}

	if (irq_status & EMIF_WR_ECC_ERR)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci, 1,
				     0, 0, -1, 0, 0, 0,
				     mci->ctl_name, "WR");

	ti_edac_writel(edac, irq_status, EMIF_IRQ_STATUS);

	return IRQ_HANDLED;
}