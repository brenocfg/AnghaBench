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
typedef  int u8 ;
typedef  int u32 ;
struct mem_ctl_info {int /*<<< orphan*/  pdev; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASPEED_MCR_ADDR_REC ; 
 int /*<<< orphan*/  ASPEED_MCR_ADDR_UNREC ; 
 int /*<<< orphan*/  ASPEED_MCR_INTR_CTRL ; 
 int /*<<< orphan*/  ASPEED_MCR_INTR_CTRL_CLEAR ; 
 int ASPEED_MCR_INTR_CTRL_CNT_REC ; 
 int ASPEED_MCR_INTR_CTRL_CNT_UNREC ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  aspeed_regmap ; 
 int /*<<< orphan*/  count_rec (struct mem_ctl_info*,int,int) ; 
 int /*<<< orphan*/  count_un_rec (struct mem_ctl_info*,int,int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t mcr_isr(int irq, void *arg)
{
	struct mem_ctl_info *mci = arg;
	u32 rec_addr, un_rec_addr;
	u32 reg50, reg5c, reg58;
	u8  rec_cnt, un_rec_cnt;

	regmap_read(aspeed_regmap, ASPEED_MCR_INTR_CTRL, &reg50);
	dev_dbg(mci->pdev, "received edac interrupt w/ mcr register 50: 0x%x\n",
		reg50);

	/* collect data about recoverable and unrecoverable errors */
	rec_cnt = (reg50 & ASPEED_MCR_INTR_CTRL_CNT_REC) >> 16;
	un_rec_cnt = (reg50 & ASPEED_MCR_INTR_CTRL_CNT_UNREC) >> 12;

	dev_dbg(mci->pdev, "%d recoverable interrupts and %d unrecoverable interrupts\n",
		rec_cnt, un_rec_cnt);

	regmap_read(aspeed_regmap, ASPEED_MCR_ADDR_UNREC, &reg58);
	un_rec_addr = reg58;

	regmap_read(aspeed_regmap, ASPEED_MCR_ADDR_REC, &reg5c);
	rec_addr = reg5c;

	/* clear interrupt flags and error counters: */
	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_CLEAR,
			   ASPEED_MCR_INTR_CTRL_CLEAR);

	regmap_update_bits(aspeed_regmap, ASPEED_MCR_INTR_CTRL,
			   ASPEED_MCR_INTR_CTRL_CLEAR, 0);

	/* process recoverable and unrecoverable errors */
	count_rec(mci, rec_cnt, rec_addr);
	count_un_rec(mci, un_rec_cnt, un_rec_addr);

	if (!rec_cnt && !un_rec_cnt)
		dev_dbg(mci->pdev, "received edac interrupt, but did not find any ECC counters\n");

	regmap_read(aspeed_regmap, ASPEED_MCR_INTR_CTRL, &reg50);
	dev_dbg(mci->pdev, "edac interrupt handled. mcr reg 50 is now: 0x%x\n",
		reg50);

	return IRQ_HANDLED;
}