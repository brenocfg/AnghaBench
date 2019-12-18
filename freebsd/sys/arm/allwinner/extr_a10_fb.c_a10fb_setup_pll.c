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
typedef  int /*<<< orphan*/  uint64_t ;
struct a10fb_softc {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  clk_t ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
a10fb_setup_pll(struct a10fb_softc *sc, uint64_t freq)
{
	clk_t clk_sclk1, clk_sclk2;
	int error;

	error = clk_get_by_ofw_name(sc->dev, 0, "lcd_ch1_sclk1", &clk_sclk1);
	if (error != 0) {
		device_printf(sc->dev, "cannot find clk 'lcd_ch1_sclk1'\n");
		return (error);
	}
	error = clk_get_by_ofw_name(sc->dev, 0, "lcd_ch1_sclk2", &clk_sclk2);
	if (error != 0) {
		device_printf(sc->dev, "cannot find clk 'lcd_ch1_sclk2'\n");
		return (error);
	}

	error = clk_set_freq(clk_sclk2, freq, 0);
	if (error != 0) {
		device_printf(sc->dev, "cannot set lcd ch1 frequency\n");
		return (error);
	}
	error = clk_enable(clk_sclk2);
	if (error != 0) {
		device_printf(sc->dev, "cannot enable lcd ch1 sclk2\n");
		return (error);
	}
	error = clk_enable(clk_sclk1);
	if (error != 0) {
		device_printf(sc->dev, "cannot enable lcd ch1 sclk1\n");
		return (error);
	}

	return (0);
}