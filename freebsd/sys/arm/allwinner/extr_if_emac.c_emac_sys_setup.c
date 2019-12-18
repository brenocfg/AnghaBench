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
struct emac_softc {int /*<<< orphan*/  emac_dev; int /*<<< orphan*/  emac_clk; } ;

/* Variables and functions */
 int /*<<< orphan*/  a10_map_to_emac () ; 
 int clk_enable (int /*<<< orphan*/ ) ; 
 int clk_get_by_ofw_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
emac_sys_setup(struct emac_softc *sc)
{
	int error;

	/* Activate EMAC clock. */
	error = clk_get_by_ofw_index(sc->emac_dev, 0, 0, &sc->emac_clk);
	if (error != 0) {
		device_printf(sc->emac_dev, "cannot get clock\n");
		return (error);
	}
	error = clk_enable(sc->emac_clk);
	if (error != 0) {
		device_printf(sc->emac_dev, "cannot enable clock\n");
		return (error);
	}

	/* Map sram. */
	a10_map_to_emac();

	return (0);
}