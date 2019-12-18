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
struct rk_i2c_softc {int /*<<< orphan*/  mtx; int /*<<< orphan*/ * res; int /*<<< orphan*/ * intrhand; int /*<<< orphan*/  dev; int /*<<< orphan*/ * pclk; int /*<<< orphan*/ * sclk; int /*<<< orphan*/ * iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_teardown_intr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clk_release (int /*<<< orphan*/ *) ; 
 int device_delete_child (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct rk_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rk_i2c_spec ; 

__attribute__((used)) static int
rk_i2c_detach(device_t dev)
{
	struct rk_i2c_softc *sc;
	int error;

	sc = device_get_softc(dev);

	if ((error = bus_generic_detach(dev)) != 0)
		return (error);

	if (sc->iicbus != NULL)
		if ((error = device_delete_child(dev, sc->iicbus)) != 0)
			return (error);

	if (sc->sclk != NULL)
		clk_release(sc->sclk);
	if (sc->pclk != NULL)
		clk_release(sc->pclk);

	if (sc->intrhand != NULL)
		bus_teardown_intr(sc->dev, sc->res[1], sc->intrhand);

	bus_release_resources(dev, rk_i2c_spec, sc->res);

	mtx_destroy(&sc->mtx);

	return (0);
}