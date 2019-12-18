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
struct clkbrd_softc {int /*<<< orphan*/ * sc_bh; int /*<<< orphan*/ * sc_bt; int /*<<< orphan*/  sc_clk_ctrl; int /*<<< orphan*/  sc_led_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 size_t CLKBRD_CLK ; 
 int /*<<< orphan*/  CLK_CTRL ; 
 int /*<<< orphan*/  bus_space_read_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_space_write_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clkbrd_free_resources (struct clkbrd_softc*) ; 
 struct clkbrd_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  led_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
clkbrd_detach(device_t dev)
{
	struct clkbrd_softc *sc;

	sc = device_get_softc(dev);

	led_destroy(sc->sc_led_dev);
	bus_space_write_1(sc->sc_bt[CLKBRD_CLK], sc->sc_bh[CLKBRD_CLK],
	    CLK_CTRL, sc->sc_clk_ctrl);
	bus_space_read_1(sc->sc_bt[CLKBRD_CLK], sc->sc_bh[CLKBRD_CLK],
	    CLK_CTRL);
	clkbrd_free_resources(sc);

	return (0);
}