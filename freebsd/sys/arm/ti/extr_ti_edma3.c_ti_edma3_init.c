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
typedef  int uint32_t ;

/* Variables and functions */
 scalar_t__ EDMA_TPTC0_CLK ; 
 int /*<<< orphan*/  TI_EDMA3CC_CCERRCLR ; 
 int /*<<< orphan*/  TI_EDMA3CC_DCHMAP (int) ; 
 int /*<<< orphan*/  TI_EDMA3CC_DMAQNUM (int) ; 
 int TI_EDMA3CC_DMAQNUM_CLR (int) ; 
 int TI_EDMA3CC_DMAQNUM_SET (int,unsigned int) ; 
 int /*<<< orphan*/  TI_EDMA3CC_DRAE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_DRAEH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_EMCR ; 
 int /*<<< orphan*/  TI_EDMA3CC_EMCRH ; 
 int /*<<< orphan*/  TI_EDMA3CC_QDMAQNUM ; 
 int TI_EDMA3CC_QDMAQNUM_CLR (int) ; 
 int TI_EDMA3CC_QDMAQNUM_SET (int,unsigned int) ; 
 int /*<<< orphan*/  TI_EDMA3CC_QEMCR ; 
 int /*<<< orphan*/  TI_EDMA3CC_QRAE (int /*<<< orphan*/ ) ; 
 int TI_EDMA3_NUM_DMA_CHS ; 
 int TI_EDMA3_NUM_QDMA_CHS ; 
 int ti_edma3_cc_rd_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_edma3_cc_wr_4 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ti_prcm_clk_enable (scalar_t__) ; 

void
ti_edma3_init(unsigned int eqn)
{
	uint32_t reg;
	int i;

	/* on AM335x Event queue 0 is always mapped to Transfer Controller 0,
	 * event queue 1 to TC2, etc. So we are asking PRCM to power on specific
	 * TC based on what event queue we need to initialize */
	ti_prcm_clk_enable(EDMA_TPTC0_CLK + eqn);

	/* Clear Event Missed Regs */
	ti_edma3_cc_wr_4(TI_EDMA3CC_EMCR, 0xFFFFFFFF);
	ti_edma3_cc_wr_4(TI_EDMA3CC_EMCRH, 0xFFFFFFFF);
	ti_edma3_cc_wr_4(TI_EDMA3CC_QEMCR, 0xFFFFFFFF);

	/* Clear Error Reg */
	ti_edma3_cc_wr_4(TI_EDMA3CC_CCERRCLR, 0xFFFFFFFF);

	/* Enable DMA channels 0-63 */
	ti_edma3_cc_wr_4(TI_EDMA3CC_DRAE(0), 0xFFFFFFFF);
	ti_edma3_cc_wr_4(TI_EDMA3CC_DRAEH(0), 0xFFFFFFFF);

	for (i = 0; i < 64; i++) {
		ti_edma3_cc_wr_4(TI_EDMA3CC_DCHMAP(i), i<<5);
	}

	/* Initialize the DMA Queue Number Registers */
	for (i = 0; i < TI_EDMA3_NUM_DMA_CHS; i++) {
		reg = ti_edma3_cc_rd_4(TI_EDMA3CC_DMAQNUM(i>>3));
		reg &= TI_EDMA3CC_DMAQNUM_CLR(i);
		reg |= TI_EDMA3CC_DMAQNUM_SET(i, eqn);
		ti_edma3_cc_wr_4(TI_EDMA3CC_DMAQNUM(i>>3), reg);
	}

	/* Enable the QDMA Region access for all channels */
	ti_edma3_cc_wr_4(TI_EDMA3CC_QRAE(0), (1 << TI_EDMA3_NUM_QDMA_CHS) - 1);

	/*Initialize QDMA Queue Number Registers */
	for (i = 0; i < TI_EDMA3_NUM_QDMA_CHS; i++) {
		reg = ti_edma3_cc_rd_4(TI_EDMA3CC_QDMAQNUM);
		reg &= TI_EDMA3CC_QDMAQNUM_CLR(i);
		reg |= TI_EDMA3CC_QDMAQNUM_SET(i, eqn);
		ti_edma3_cc_wr_4(TI_EDMA3CC_QDMAQNUM, reg);
	}
}