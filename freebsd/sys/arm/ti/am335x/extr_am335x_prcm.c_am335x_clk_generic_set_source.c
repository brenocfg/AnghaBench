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
struct ti_clock_dev {int /*<<< orphan*/  id; } ;
struct am335x_prcm_softc {int dummy; } ;
struct am335x_clk_details {int /*<<< orphan*/  clksel_reg; } ;
typedef  int clk_src_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
#define  EXT_CLK 130 
#define  F32KHZ_CLK 129 
#define  SYSCLK_CLK 128 
 struct am335x_clk_details* am335x_clk_details (int /*<<< orphan*/ ) ; 
 struct am335x_prcm_softc* am335x_prcm_sc ; 
 int prcm_read_4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prcm_write_4 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
am335x_clk_generic_set_source(struct ti_clock_dev *clkdev, clk_src_t clksrc)
{
	struct am335x_prcm_softc *sc = am335x_prcm_sc;
	struct am335x_clk_details* clk_details;
	uint32_t reg;

	if (sc == NULL)
		return ENXIO;

	clk_details = am335x_clk_details(clkdev->id);

	if (clk_details == NULL)
		return (ENXIO);

	switch (clksrc) {
		case EXT_CLK:
			reg = 0; /* SEL2: TCLKIN clock */
			break;
		case SYSCLK_CLK:
			reg = 1; /* SEL1: CLK_M_OSC clock */
			break;
		case F32KHZ_CLK:
			reg = 2; /* SEL3: CLK_32KHZ clock */
			break;
		default:
			return (ENXIO);
	}

	prcm_write_4(clk_details->clksel_reg, reg);
	while ((prcm_read_4(clk_details->clksel_reg) & 0x3) != reg)
		DELAY(10);

	return (0);
}