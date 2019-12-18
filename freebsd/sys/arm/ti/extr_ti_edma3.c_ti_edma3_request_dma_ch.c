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
 int EINVAL ; 
 int /*<<< orphan*/  TI_EDMA3CC_DMAQNUM (unsigned int) ; 
 int TI_EDMA3CC_DMAQNUM_CLR (unsigned int) ; 
 int TI_EDMA3CC_DMAQNUM_SET (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  TI_EDMA3CC_DRAE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_DRAEH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_OPT (unsigned int) ; 
 int TI_EDMA3CC_OPT_TCC_CLR ; 
 int TI_EDMA3CC_OPT_TCC_SET (unsigned int) ; 
 unsigned int TI_EDMA3_NUM_DMA_CHS ; 
 int ti_edma3_cc_rd_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ti_edma3_cc_wr_4 (int /*<<< orphan*/ ,int) ; 

int
ti_edma3_request_dma_ch(unsigned int ch, unsigned int tccn, unsigned int eqn)
{
	uint32_t reg;

	if (ch >= TI_EDMA3_NUM_DMA_CHS)
		return (EINVAL);

	/* Enable the DMA channel in the DRAE/DRAEH registers */
	if (ch < 32) {
		reg = ti_edma3_cc_rd_4(TI_EDMA3CC_DRAE(0));
		reg |= (0x01 << ch);
		ti_edma3_cc_wr_4(TI_EDMA3CC_DRAE(0), reg);
	} else {
		reg = ti_edma3_cc_rd_4(TI_EDMA3CC_DRAEH(0));
		reg |= (0x01 << (ch - 32));
		ti_edma3_cc_wr_4(TI_EDMA3CC_DRAEH(0), reg);
	}

	/* Associate DMA Channel to Event Queue */
	reg = ti_edma3_cc_rd_4(TI_EDMA3CC_DMAQNUM(ch >> 3));
	reg &= TI_EDMA3CC_DMAQNUM_CLR(ch);
	reg |= TI_EDMA3CC_DMAQNUM_SET((ch), eqn);
	ti_edma3_cc_wr_4(TI_EDMA3CC_DMAQNUM(ch >> 3), reg);

	/* Set TCC in corresponding PaRAM Entry */
	reg = ti_edma3_cc_rd_4(TI_EDMA3CC_OPT(ch));
	reg &= TI_EDMA3CC_OPT_TCC_CLR;
	reg |= TI_EDMA3CC_OPT_TCC_SET(ch);
	ti_edma3_cc_wr_4(TI_EDMA3CC_OPT(ch), reg);

	return 0;
}