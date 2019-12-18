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

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TI_EDMA3CC_EMCR ; 
 int /*<<< orphan*/  TI_EDMA3CC_EMCRH ; 
 int /*<<< orphan*/  TI_EDMA3CC_S_EESR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_S_EESRH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_S_SECR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TI_EDMA3CC_S_SECRH (int /*<<< orphan*/ ) ; 
 unsigned int TI_EDMA3_NUM_DMA_CHS ; 
 int /*<<< orphan*/  ti_edma3_cc_wr_4 (int /*<<< orphan*/ ,int) ; 

int
ti_edma3_enable_transfer_event(unsigned int ch)
{
	if (ch >= TI_EDMA3_NUM_DMA_CHS)
		return (EINVAL);

	/* Clear SECR(H) & EMCR(H) to clean any previous NULL request
	 * and set corresponding bit in EESR to enable DMA event */
	if(ch < 32) {
		ti_edma3_cc_wr_4(TI_EDMA3CC_S_SECR(0), (1 << ch));
		ti_edma3_cc_wr_4(TI_EDMA3CC_EMCR, (1 << ch));
		ti_edma3_cc_wr_4(TI_EDMA3CC_S_EESR(0), (1 << ch));
	} else {
		ti_edma3_cc_wr_4(TI_EDMA3CC_S_SECRH(0), 1 << (ch - 32));
		ti_edma3_cc_wr_4(TI_EDMA3CC_EMCRH, 1 << (ch - 32));
		ti_edma3_cc_wr_4(TI_EDMA3CC_S_EESRH(0), 1 << (ch - 32));
	}

	return 0;
}