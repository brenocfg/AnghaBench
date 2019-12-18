#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  f_max; } ;
struct jz4780_mmc_softc {int /*<<< orphan*/  sc_clk; TYPE_1__ sc_host; int /*<<< orphan*/  sc_dev; } ;

/* Variables and functions */
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ ) ; 
 int clk_set_freq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
jz4780_mmc_enable_clock(struct jz4780_mmc_softc *sc)
{
	int err;

	err = clk_get_by_ofw_name(sc->sc_dev, 0, "mmc", &sc->sc_clk);
	if (err == 0)
		err = clk_enable(sc->sc_clk);
	if (err == 0)
		err = clk_set_freq(sc->sc_clk, sc->sc_host.f_max, 0);
	if (err != 0)
		clk_release(sc->sc_clk);
	return (err);
}