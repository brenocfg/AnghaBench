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
struct resource {int dummy; } ;
struct omap4_prcm_softc {struct resource* sc_res; } ;
struct omap4_clk_details {int /*<<< orphan*/  clksel_reg; int /*<<< orphan*/  instance; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 unsigned int FREQ_32KHZ ; 
 int bus_read_4 (struct resource*,int /*<<< orphan*/ ) ; 
 struct omap4_clk_details* omap4_clk_details (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_clk_get_sysclk_freq (int /*<<< orphan*/ *,unsigned int*) ; 
 struct omap4_prcm_softc* omap4_prcm_get_instance_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
omap4_clk_gptimer_get_source_freq(struct ti_clock_dev *clkdev,
                                  unsigned int *freq
                                  )
{
	struct omap4_prcm_softc *sc;
	struct omap4_clk_details* clk_details;
	struct resource* clk_mem_res;
	uint32_t clksel;
	unsigned int src_freq;

	clk_details = omap4_clk_details(clkdev->id);

	if (clk_details == NULL)
		return (ENXIO);

	sc = omap4_prcm_get_instance_softc(clk_details->instance);
	if (sc == NULL)
		return ENXIO;

	clk_mem_res = sc->sc_res;

	if (clk_mem_res == NULL)
		return (EINVAL);
	
	/* Need to read the CLKSEL field to determine the clock source */
	clksel = bus_read_4(clk_mem_res, clk_details->clksel_reg);
	if (clksel & (0x1UL << 24))
		src_freq = FREQ_32KHZ;
	else
		omap4_clk_get_sysclk_freq(NULL, &src_freq);
	
	/* Return the frequency */
	if (freq)
		*freq = src_freq;
	
	return (0);
}