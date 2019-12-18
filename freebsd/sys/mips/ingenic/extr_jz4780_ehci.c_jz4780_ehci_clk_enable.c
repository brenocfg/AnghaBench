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
struct jz4780_ehci_softc {int /*<<< orphan*/  clk; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct jz4780_ehci_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
jz4780_ehci_clk_enable(device_t dev)
{
	struct jz4780_ehci_softc *sc;
	int err;

	sc = device_get_softc(dev);

	err = clk_get_by_ofw_index(dev, 0, 0, &sc->clk);
	if (err != 0) {
		device_printf(dev, "unable to lookup device clock\n");
		return (err);
	}
	err = clk_enable(sc->clk);
	if (err != 0) {
		device_printf(dev, "unable to enable device clock\n");
		return (err);
	}
	err = clk_set_freq(sc->clk, 48000000, 0);
	if (err != 0) {
		device_printf(dev, "unable to set device clock to 48 kHZ\n");
		return (err);
	}
	return (0);
}