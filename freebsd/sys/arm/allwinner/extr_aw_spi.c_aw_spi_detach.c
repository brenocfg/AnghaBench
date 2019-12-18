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
struct aw_spi_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/ * intrhand; int /*<<< orphan*/  dev; scalar_t__ rst_ahb; int /*<<< orphan*/ * clk_ahb; int /*<<< orphan*/ * clk_mod; int /*<<< orphan*/ * spibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  aw_spi_spec ; 
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct aw_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hwreset_assert (scalar_t__) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aw_spi_detach(device_t dev)
{
	struct aw_spi_softc *sc;

	sc = device_get_softc(dev);

	bus_generic_detach(sc->dev);
	if (sc->spibus != NULL)
		device_delete_child(dev, sc->spibus);

	if (sc->clk_mod != NULL)
		clk_release(sc->clk_mod);
	if (sc->clk_ahb)
		clk_release(sc->clk_ahb);
	if (sc->rst_ahb)
		hwreset_assert(sc->rst_ahb);

	if (sc->intrhand != NULL)
		bus_teardown_intr(sc->dev, sc->res[1], sc->intrhand);

	bus_release_resources(dev, aw_spi_spec, sc->res);
	mtx_destroy(&sc->mtx);

	return (0);
}