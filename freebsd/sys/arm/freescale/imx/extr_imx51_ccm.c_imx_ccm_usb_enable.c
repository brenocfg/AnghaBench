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
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCGR_CLK_MODE_ALWAYS ; 
 int /*<<< orphan*/  CCGR_USBOH3_60M_CLK ; 
 int /*<<< orphan*/  CCGR_USBOH3_IPG_AHB_CLK ; 
 int /*<<< orphan*/  CCMC_CSCDR1 ; 
 int /*<<< orphan*/  CCMC_CSCMR1 ; 
 int CSCDR1_USBOH3_CLK_PODF_MASK ; 
 int CSCDR1_USBOH3_CLK_PODF_SHIFT ; 
 int CSCDR1_USBOH3_CLK_PRED_MASK ; 
 int CSCDR1_USBOH3_CLK_PRED_SHIFT ; 
 int CSCMR1_USBOH3_CLK_SEL_MASK ; 
 int CSCMR1_USBOH3_CLK_SEL_SHIFT ; 
 int ccm_read_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccm_softc ; 
 int /*<<< orphan*/  ccm_write_4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  imx51_clk_gating (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
imx_ccm_usb_enable(device_t dev)
{
	uint32_t regval;

	/*
	 * Select PLL2 as the source for the USB clock.
	 * The default is PLL3, but U-boot changes it to PLL2.
	 */
	regval = ccm_read_4(ccm_softc, CCMC_CSCMR1);
	regval &= ~CSCMR1_USBOH3_CLK_SEL_MASK;
	regval |= 1 << CSCMR1_USBOH3_CLK_SEL_SHIFT;
	ccm_write_4(ccm_softc, CCMC_CSCMR1, regval);

	/*
	 * Set the USB clock pre-divider to div-by-5, post-divider to div-by-2.
	 */
	regval = ccm_read_4(ccm_softc, CCMC_CSCDR1);
	regval &= ~CSCDR1_USBOH3_CLK_PODF_MASK;
	regval &= ~CSCDR1_USBOH3_CLK_PRED_MASK;
	regval |= 4 << CSCDR1_USBOH3_CLK_PRED_SHIFT;
	regval |= 1 << CSCDR1_USBOH3_CLK_PODF_SHIFT;
	ccm_write_4(ccm_softc, CCMC_CSCDR1, regval);

	/*
	 * The same two clocks gates are used on imx51 and imx53.
	 */
	imx51_clk_gating(CCGR_USBOH3_IPG_AHB_CLK, CCGR_CLK_MODE_ALWAYS);
	imx51_clk_gating(CCGR_USBOH3_60M_CLK, CCGR_CLK_MODE_ALWAYS);
}