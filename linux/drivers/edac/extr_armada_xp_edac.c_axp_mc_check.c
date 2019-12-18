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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mem_ctl_info {int /*<<< orphan*/  ctl_name; int /*<<< orphan*/  pdev; struct axp_mc_drvdata* pvt_info; } ;
struct axp_mc_drvdata {char* msg; scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HW_EVENT_ERR_CORRECTED ; 
 int /*<<< orphan*/  HW_EVENT_ERR_UNCORRECTED ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int SDRAM_ERR_ADDR_BANK_MASK ; 
 int SDRAM_ERR_ADDR_BANK_OFFSET ; 
 int SDRAM_ERR_ADDR_COL_MASK ; 
 int SDRAM_ERR_ADDR_COL_OFFSET ; 
 int SDRAM_ERR_ADDR_CS_MASK ; 
 int SDRAM_ERR_ADDR_CS_OFFSET ; 
 scalar_t__ SDRAM_ERR_ADDR_REG ; 
 int SDRAM_ERR_ADDR_TYPE_MASK ; 
 scalar_t__ SDRAM_ERR_CALC_ECC_REG ; 
 int SDRAM_ERR_CALC_ECC_ROW_MASK ; 
 int SDRAM_ERR_CALC_ECC_ROW_OFFSET ; 
 int SDRAM_ERR_CAUSE_DBE_MASK ; 
 scalar_t__ SDRAM_ERR_CAUSE_ERR_REG ; 
 scalar_t__ SDRAM_ERR_CAUSE_MSG_REG ; 
 int SDRAM_ERR_CAUSE_SBE_MASK ; 
 scalar_t__ SDRAM_ERR_DATA_H_REG ; 
 scalar_t__ SDRAM_ERR_DATA_L_REG ; 
 scalar_t__ SDRAM_ERR_DBE_COUNT_REG ; 
 scalar_t__ SDRAM_ERR_RECV_ECC_REG ; 
 scalar_t__ SDRAM_ERR_SBE_COUNT_REG ; 
 int axp_mc_calc_address (struct axp_mc_drvdata*,int,int,int,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  edac_mc_handle_error (int /*<<< orphan*/ ,struct mem_ctl_info*,int,int,int,int,int,int,int,int /*<<< orphan*/ ,char*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void axp_mc_check(struct mem_ctl_info *mci)
{
	struct axp_mc_drvdata *drvdata = mci->pvt_info;
	uint32_t data_h, data_l, recv_ecc, calc_ecc, addr;
	uint32_t cnt_sbe, cnt_dbe, cause_err, cause_msg;
	uint32_t row_val, col_val, bank_val, addr_val;
	uint8_t syndrome_val, cs_val;
	char *msg = drvdata->msg;

	data_h    = readl(drvdata->base + SDRAM_ERR_DATA_H_REG);
	data_l    = readl(drvdata->base + SDRAM_ERR_DATA_L_REG);
	recv_ecc  = readl(drvdata->base + SDRAM_ERR_RECV_ECC_REG);
	calc_ecc  = readl(drvdata->base + SDRAM_ERR_CALC_ECC_REG);
	addr      = readl(drvdata->base + SDRAM_ERR_ADDR_REG);
	cnt_sbe   = readl(drvdata->base + SDRAM_ERR_SBE_COUNT_REG);
	cnt_dbe   = readl(drvdata->base + SDRAM_ERR_DBE_COUNT_REG);
	cause_err = readl(drvdata->base + SDRAM_ERR_CAUSE_ERR_REG);
	cause_msg = readl(drvdata->base + SDRAM_ERR_CAUSE_MSG_REG);

	/* clear cause registers */
	writel(~(SDRAM_ERR_CAUSE_DBE_MASK | SDRAM_ERR_CAUSE_SBE_MASK),
	       drvdata->base + SDRAM_ERR_CAUSE_ERR_REG);
	writel(~(SDRAM_ERR_CAUSE_DBE_MASK | SDRAM_ERR_CAUSE_SBE_MASK),
	       drvdata->base + SDRAM_ERR_CAUSE_MSG_REG);

	/* clear error counter registers */
	if (cnt_sbe)
		writel(0, drvdata->base + SDRAM_ERR_SBE_COUNT_REG);
	if (cnt_dbe)
		writel(0, drvdata->base + SDRAM_ERR_DBE_COUNT_REG);

	if (!cnt_sbe && !cnt_dbe)
		return;

	if (!(addr & SDRAM_ERR_ADDR_TYPE_MASK)) {
		if (cnt_sbe)
			cnt_sbe--;
		else
			dev_warn(mci->pdev, "inconsistent SBE count detected");
	} else {
		if (cnt_dbe)
			cnt_dbe--;
		else
			dev_warn(mci->pdev, "inconsistent DBE count detected");
	}

	/* report earlier errors */
	if (cnt_sbe)
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				     cnt_sbe, /* error count */
				     0, 0, 0, /* pfn, offset, syndrome */
				     -1, -1, -1, /* top, mid, low layer */
				     mci->ctl_name,
				     "details unavailable (multiple errors)");
	if (cnt_dbe)
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				     cnt_sbe, /* error count */
				     0, 0, 0, /* pfn, offset, syndrome */
				     -1, -1, -1, /* top, mid, low layer */
				     mci->ctl_name,
				     "details unavailable (multiple errors)");

	/* report details for most recent error */
	cs_val   = (addr & SDRAM_ERR_ADDR_CS_MASK) >> SDRAM_ERR_ADDR_CS_OFFSET;
	bank_val = (addr & SDRAM_ERR_ADDR_BANK_MASK) >> SDRAM_ERR_ADDR_BANK_OFFSET;
	row_val  = (calc_ecc & SDRAM_ERR_CALC_ECC_ROW_MASK) >> SDRAM_ERR_CALC_ECC_ROW_OFFSET;
	col_val  = (addr & SDRAM_ERR_ADDR_COL_MASK) >> SDRAM_ERR_ADDR_COL_OFFSET;
	syndrome_val = (recv_ecc ^ calc_ecc) & 0xff;
	addr_val = axp_mc_calc_address(drvdata, cs_val, bank_val, row_val,
				       col_val);
	msg += sprintf(msg, "row=0x%04x ", row_val); /* 11 chars */
	msg += sprintf(msg, "bank=0x%x ", bank_val); /*  9 chars */
	msg += sprintf(msg, "col=0x%04x ", col_val); /* 11 chars */
	msg += sprintf(msg, "cs=%d", cs_val);	     /*  4 chars */

	if (!(addr & SDRAM_ERR_ADDR_TYPE_MASK)) {
		edac_mc_handle_error(HW_EVENT_ERR_CORRECTED, mci,
				     1,	/* error count */
				     addr_val >> PAGE_SHIFT,
				     addr_val & ~PAGE_MASK,
				     syndrome_val,
				     cs_val, -1, -1, /* top, mid, low layer */
				     mci->ctl_name, drvdata->msg);
	} else {
		edac_mc_handle_error(HW_EVENT_ERR_UNCORRECTED, mci,
				     1,	/* error count */
				     addr_val >> PAGE_SHIFT,
				     addr_val & ~PAGE_MASK,
				     syndrome_val,
				     cs_val, -1, -1, /* top, mid, low layer */
				     mci->ctl_name, drvdata->msg);
	}
}