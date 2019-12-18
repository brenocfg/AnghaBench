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
struct omap4_prcm_softc {int attach_done; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_PASS_ORDER_EARLY ; 
 scalar_t__ BUS_PASS_TIMER ; 
 int /*<<< orphan*/  arm_tmr_change_frequency (unsigned int) ; 
 scalar_t__ bus_current_pass ; 
 int /*<<< orphan*/  bus_generic_new_pass (int /*<<< orphan*/ ) ; 
 struct omap4_prcm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int device_get_unit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  omap4_clk_get_arm_fclk_freq (int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static void
omap4_prcm_new_pass(device_t dev)
{
	struct omap4_prcm_softc *sc = device_get_softc(dev);
	unsigned int freq;

	if (sc->attach_done ||
	  bus_current_pass < (BUS_PASS_TIMER + BUS_PASS_ORDER_EARLY)) {
		bus_generic_new_pass(dev);
		return;
	}
	sc->attach_done = 1;

	/*
	 * In order to determine ARM frequency we need both RPM and CM1 
	 * instances up and running. So wait until all CRM devices are
	 * initialized. Should be replaced with proper clock framework
	 */
	if (device_get_unit(dev) == 2) {
		omap4_clk_get_arm_fclk_freq(NULL, &freq);
		arm_tmr_change_frequency(freq / 2);
	}

	return;
}