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
struct i2c_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; scalar_t__ rid; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int IIC_NOERR ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  RF_ACTIVE ; 
 int /*<<< orphan*/  SYS_RES_MEMORY ; 
 int /*<<< orphan*/ * bus_alloc_resource_any (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
i2c_attach(device_t dev)
{
	struct i2c_softc *sc;
	sc = device_get_softc(dev);

	sc->dev = dev;
	sc->rid = 0;

	mtx_init(&sc->mutex, device_get_nameunit(dev), "I2C", MTX_DEF);

	sc->res = bus_alloc_resource_any(dev, SYS_RES_MEMORY, &sc->rid,
	    RF_ACTIVE);
	if (sc->res == NULL) {
		device_printf(dev, "could not allocate resources");
		mtx_destroy(&sc->mutex);
		return (ENXIO);
	}

	sc->bst = rman_get_bustag(sc->res);
	sc->bsh = rman_get_bushandle(sc->res);

	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "could not add iicbus child");
		mtx_destroy(&sc->mutex);
		return (ENXIO);
	}

	bus_generic_attach(dev);
	return (IIC_NOERR);
}