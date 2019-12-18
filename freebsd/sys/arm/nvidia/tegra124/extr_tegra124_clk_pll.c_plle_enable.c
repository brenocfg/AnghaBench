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
struct mnp_bits {int dummy; } ;
struct pll_sc {int /*<<< orphan*/  misc_reg; int /*<<< orphan*/  base_reg; struct mnp_bits mnp_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int /*<<< orphan*/  PCIE_PLL_CFG0 ; 
 int PCIE_PLL_CFG0_SEQ_ENABLE ; 
 int /*<<< orphan*/  PLLE_AUX ; 
 int PLLE_AUX_ENABLE_SWCTL ; 
 int PLLE_AUX_SEQ_ENABLE ; 
 int PLLE_AUX_SEQ_START_STATE ; 
 int PLLE_AUX_SS_SWCTL ; 
 int PLLE_AUX_USE_LOCKDET ; 
 int PLLE_BASE_DIVCML_MASK ; 
 int PLLE_BASE_DIVCML_SHIFT ; 
 int PLLE_BASE_LOCK_OVERRIDE ; 
 int PLLE_MISC_IDDQ_OVERRIDE_VALUE ; 
 int PLLE_MISC_IDDQ_SWCTL ; 
 int PLLE_MISC_LOCK_ENABLE ; 
 int PLLE_MISC_PTS ; 
 int PLLE_MISC_VREG_BG_CTRL_MASK ; 
 int PLLE_MISC_VREG_CTRL_MASK ; 
 int /*<<< orphan*/  PLLE_SS_CNTL ; 
 int PLLE_SS_CNTL_BYPASS_SS ; 
 int PLLE_SS_CNTL_COEFFICIENTS_MASK ; 
 int PLLE_SS_CNTL_COEFFICIENTS_VAL ; 
 int PLLE_SS_CNTL_DISABLE ; 
 int PLLE_SS_CNTL_INTERP_RESET ; 
 int PLLE_SS_CNTL_SSCBYP ; 
 int PLLE_SS_CNTL_SSCCENTER ; 
 int PLLE_SS_CNTL_SSCINVERT ; 
 int /*<<< orphan*/  RD4 (struct pll_sc*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SATA_PLL_CFG0 ; 
 int SATA_PLL_CFG0_PADPLL_RESET_OVERRIDE_VALUE ; 
 int SATA_PLL_CFG0_PADPLL_RESET_SWCTL ; 
 int SATA_PLL_CFG0_PADPLL_USE_LOCKDET ; 
 int SATA_PLL_CFG0_SEQ_ENABLE ; 
 int SATA_PLL_CFG0_SEQ_IN_SWCTL ; 
 int SATA_PLL_CFG0_SEQ_LANE_PD_INPUT_VALUE ; 
 int SATA_PLL_CFG0_SEQ_PADPLL_PD_INPUT_VALUE ; 
 int SATA_PLL_CFG0_SEQ_RESET_INPUT_VALUE ; 
 int SATA_PLL_CFG0_SEQ_START_STATE ; 
 int /*<<< orphan*/  WR4 (struct pll_sc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XUSBIO_PLL_CFG0 ; 
 int XUSBIO_PLL_CFG0_CLK_ENABLE_SWCTL ; 
 int XUSBIO_PLL_CFG0_PADPLL_RESET_SWCTL ; 
 int XUSBIO_PLL_CFG0_PADPLL_USE_LOCKDET ; 
 int XUSBIO_PLL_CFG0_SEQ_ENABLE ; 
 int XUSBIO_PLL_CFG0_SEQ_START_STATE ; 
 int /*<<< orphan*/  pll_enable (struct pll_sc*) ; 
 int set_divisors (struct pll_sc*,int,int,int,int) ; 
 int wait_for_lock (struct pll_sc*) ; 

__attribute__((used)) static int
plle_enable(struct pll_sc *sc)
{
	uint32_t reg;
	int rv;
	struct mnp_bits *mnp_bits;
	uint32_t pll_m = 1;
	uint32_t pll_n = 200;
	uint32_t pll_p = 13;
	uint32_t pll_cml = 13;

	mnp_bits = &sc->mnp_bits;


	/* Disable lock override. */
	RD4(sc, sc->base_reg, &reg);
	reg &= ~PLLE_BASE_LOCK_OVERRIDE;
	WR4(sc, sc->base_reg, reg);

	RD4(sc, PLLE_AUX, &reg);
	reg |= PLLE_AUX_ENABLE_SWCTL;
	reg &= ~PLLE_AUX_SEQ_ENABLE;
	WR4(sc, PLLE_AUX, reg);
	DELAY(10);

	RD4(sc, sc->misc_reg, &reg);
	reg |= PLLE_MISC_LOCK_ENABLE;
	reg |= PLLE_MISC_IDDQ_SWCTL;
	reg &= ~PLLE_MISC_IDDQ_OVERRIDE_VALUE;
	reg |= PLLE_MISC_PTS;
	reg |= PLLE_MISC_VREG_BG_CTRL_MASK;
	reg |= PLLE_MISC_VREG_CTRL_MASK;
	WR4(sc, sc->misc_reg, reg);
	DELAY(10);

	RD4(sc, PLLE_SS_CNTL, &reg);
	reg |= PLLE_SS_CNTL_DISABLE;
	WR4(sc, PLLE_SS_CNTL, reg);

	RD4(sc, sc->base_reg, &reg);
	reg = set_divisors(sc, reg, pll_m, pll_n, pll_p);
	reg &= ~(PLLE_BASE_DIVCML_MASK << PLLE_BASE_DIVCML_SHIFT);
	reg |= pll_cml << PLLE_BASE_DIVCML_SHIFT;
	WR4(sc, sc->base_reg, reg);
	DELAY(10);

	pll_enable(sc);
	rv = wait_for_lock(sc);
	if (rv != 0)
		return (rv);

	RD4(sc, PLLE_SS_CNTL, &reg);
	reg &= ~PLLE_SS_CNTL_SSCCENTER;
	reg &= ~PLLE_SS_CNTL_SSCINVERT;
	reg &= ~PLLE_SS_CNTL_COEFFICIENTS_MASK;
	reg |= PLLE_SS_CNTL_COEFFICIENTS_VAL;
	WR4(sc, PLLE_SS_CNTL, reg);
	reg &= ~PLLE_SS_CNTL_SSCBYP;
	reg &= ~PLLE_SS_CNTL_BYPASS_SS;
	WR4(sc, PLLE_SS_CNTL, reg);
	DELAY(10);

	reg &= ~PLLE_SS_CNTL_INTERP_RESET;
	WR4(sc, PLLE_SS_CNTL, reg);
	DELAY(10);

	/* HW control of brick pll. */
	RD4(sc, sc->misc_reg, &reg);
	reg &= ~PLLE_MISC_IDDQ_SWCTL;
	WR4(sc, sc->misc_reg, reg);

	RD4(sc, PLLE_AUX, &reg);
	reg |= PLLE_AUX_USE_LOCKDET;
	reg |= PLLE_AUX_SEQ_START_STATE;
	reg &= ~PLLE_AUX_ENABLE_SWCTL;
	reg &= ~PLLE_AUX_SS_SWCTL;
	WR4(sc, PLLE_AUX, reg);
	reg |= PLLE_AUX_SEQ_START_STATE;
	DELAY(10);
	reg |= PLLE_AUX_SEQ_ENABLE;
	WR4(sc, PLLE_AUX, reg);

	RD4(sc, XUSBIO_PLL_CFG0, &reg);
	reg |= XUSBIO_PLL_CFG0_PADPLL_USE_LOCKDET;
	reg |= XUSBIO_PLL_CFG0_SEQ_START_STATE;
	reg &= ~XUSBIO_PLL_CFG0_CLK_ENABLE_SWCTL;
	reg &= ~XUSBIO_PLL_CFG0_PADPLL_RESET_SWCTL;
	WR4(sc, XUSBIO_PLL_CFG0, reg);
	DELAY(10);

	reg |= XUSBIO_PLL_CFG0_SEQ_ENABLE;
	WR4(sc, XUSBIO_PLL_CFG0, reg);


	/* Enable HW control and unreset SATA PLL. */
	RD4(sc, SATA_PLL_CFG0, &reg);
	reg &= ~SATA_PLL_CFG0_PADPLL_RESET_SWCTL;
	reg &= ~SATA_PLL_CFG0_PADPLL_RESET_OVERRIDE_VALUE;
	reg |=  SATA_PLL_CFG0_PADPLL_USE_LOCKDET;
	reg &= ~SATA_PLL_CFG0_SEQ_IN_SWCTL;
	reg &= ~SATA_PLL_CFG0_SEQ_RESET_INPUT_VALUE;
	reg &= ~SATA_PLL_CFG0_SEQ_LANE_PD_INPUT_VALUE;
	reg &= ~SATA_PLL_CFG0_SEQ_PADPLL_PD_INPUT_VALUE;
	reg &= ~SATA_PLL_CFG0_SEQ_ENABLE;
	reg |=  SATA_PLL_CFG0_SEQ_START_STATE;
	WR4(sc, SATA_PLL_CFG0, reg);
	DELAY(10);
	reg |= SATA_PLL_CFG0_SEQ_ENABLE;
	WR4(sc, SATA_PLL_CFG0, reg);

	/* Enable HW control of PCIe PLL. */
	RD4(sc, PCIE_PLL_CFG0, &reg);
	reg |= PCIE_PLL_CFG0_SEQ_ENABLE;
	WR4(sc, PCIE_PLL_CFG0, reg);

	return (0);
}