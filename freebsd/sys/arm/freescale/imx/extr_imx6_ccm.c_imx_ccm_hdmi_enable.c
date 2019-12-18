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
struct ccm_softc {int dummy; } ;

/* Variables and functions */
 int CCGR2_HDMI_TX ; 
 int CCGR2_HDMI_TX_ISFR ; 
 int /*<<< orphan*/  CCM_CCGR2 ; 
 int /*<<< orphan*/  CCM_CHSCCDR ; 
 int CHSCCDR_CLK_SEL_LDB_DI0 ; 
 int CHSCCDR_IPU1_DI0_CLK_SEL_MASK ; 
 int CHSCCDR_IPU1_DI0_CLK_SEL_SHIFT ; 
 int CHSCCDR_IPU1_DI0_PODF_MASK ; 
 int CHSCCDR_IPU1_DI0_PODF_SHIFT ; 
 int CHSCCDR_IPU1_DI0_PRE_CLK_SEL_MASK ; 
 int CHSCCDR_IPU1_DI0_PRE_CLK_SEL_SHIFT ; 
 int CHSCCDR_IPU_PRE_CLK_540M_PFD ; 
 int CHSCCDR_PODF_DIVIDE_BY_3 ; 
 int RD4 (struct ccm_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR4 (struct ccm_softc*,int /*<<< orphan*/ ,int) ; 
 struct ccm_softc* ccm_sc ; 

void
imx_ccm_hdmi_enable(void)
{
	struct ccm_softc *sc;
	uint32_t reg;

	sc = ccm_sc;
	reg = RD4(sc, CCM_CCGR2);
	reg |= CCGR2_HDMI_TX | CCGR2_HDMI_TX_ISFR;
	WR4(sc, CCM_CCGR2, reg);

	/* Set HDMI clock to 280MHz */
	reg = RD4(sc, CCM_CHSCCDR);
	reg &= ~(CHSCCDR_IPU1_DI0_PRE_CLK_SEL_MASK |
	    CHSCCDR_IPU1_DI0_PODF_MASK | CHSCCDR_IPU1_DI0_CLK_SEL_MASK);
	reg |= (CHSCCDR_PODF_DIVIDE_BY_3 << CHSCCDR_IPU1_DI0_PODF_SHIFT);
	reg |= (CHSCCDR_IPU_PRE_CLK_540M_PFD << CHSCCDR_IPU1_DI0_PRE_CLK_SEL_SHIFT);
	WR4(sc, CCM_CHSCCDR, reg);
	reg |= (CHSCCDR_CLK_SEL_LDB_DI0 << CHSCCDR_IPU1_DI0_CLK_SEL_SHIFT);
	WR4(sc, CCM_CHSCCDR, reg);
}