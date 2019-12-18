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
struct rk_spi_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/ * intrhand; int /*<<< orphan*/  dev; int /*<<< orphan*/ * clk_apb; int /*<<< orphan*/ * clk_spi; int /*<<< orphan*/ * spibus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rk_spi_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_spi_spec ; 

__attribute__((used)) static int
rk_spi_detach(device_t dev)
{
	struct rk_spi_softc *sc;

	sc = device_get_softc(dev);

	bus_generic_detach(sc->dev);
	if (sc->spibus != NULL)
		device_delete_child(dev, sc->spibus);

	if (sc->clk_spi != NULL)
		clk_release(sc->clk_spi);
	if (sc->clk_apb)
		clk_release(sc->clk_apb);

	if (sc->intrhand != NULL)
		bus_teardown_intr(sc->dev, sc->res[1], sc->intrhand);

	bus_release_resources(dev, rk_spi_spec, sc->res);
	mtx_destroy(&sc->mtx);

	return (0);
}