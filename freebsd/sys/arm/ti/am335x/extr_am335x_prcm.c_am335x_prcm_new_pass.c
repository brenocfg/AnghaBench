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
struct am335x_prcm_softc {int attach_done; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ BUS_PASS_ORDER_EARLY ; 
 scalar_t__ BUS_PASS_TIMER ; 
 scalar_t__ am335x_clk_get_arm_fclk_freq (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ am335x_clk_get_sysclk_freq (int /*<<< orphan*/ *,unsigned int*) ; 
 scalar_t__ bus_current_pass ; 
 int /*<<< orphan*/  bus_generic_new_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_detach (int /*<<< orphan*/ ) ; 
 struct am335x_prcm_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static void
am335x_prcm_new_pass(device_t dev)
{
	struct am335x_prcm_softc *sc = device_get_softc(dev);
	unsigned int sysclk, fclk;

	sc = device_get_softc(dev);
	if (sc->attach_done ||
	    bus_current_pass < (BUS_PASS_TIMER + BUS_PASS_ORDER_EARLY)) {
		bus_generic_new_pass(dev);
		return;
	}

	sc->attach_done = 1;

	if (am335x_clk_get_sysclk_freq(NULL, &sysclk) != 0)
		sysclk = 0;
	if (am335x_clk_get_arm_fclk_freq(NULL, &fclk) != 0)
		fclk = 0;
	if (sysclk && fclk)
		device_printf(dev, "Clocks: System %u.%01u MHz, CPU %u MHz\n",
		    sysclk/1000000, (sysclk % 1000000)/100000, fclk/1000000);
	else {
		device_printf(dev, "can't read frequencies yet (SCM device not ready?)\n");
		goto fail;
	}

	return;

fail:
	device_detach(dev);
	return;
}