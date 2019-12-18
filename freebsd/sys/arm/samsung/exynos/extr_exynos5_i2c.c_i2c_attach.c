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
struct i2c_softc {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * iicbus; int /*<<< orphan*/ * res; int /*<<< orphan*/  bsh; int /*<<< orphan*/  bst; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  I2CADD ; 
 int I2CMODE_MT ; 
 int I2CMODE_S ; 
 int /*<<< orphan*/  I2CSTAT ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int RXTX_EN ; 
 int /*<<< orphan*/  WRITE1 (struct i2c_softc*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  i2c_spec ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bushandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rman_get_bustag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
i2c_attach(device_t dev)
{
	struct i2c_softc *sc;
	int reg;

	sc = device_get_softc(dev);
	sc->dev = dev;

	mtx_init(&sc->mutex, device_get_nameunit(dev), "I2C", MTX_DEF);

	if (bus_alloc_resources(dev, i2c_spec, sc->res)) {
		device_printf(dev, "could not allocate resources\n");
		return (ENXIO);
	}

	/* Memory interface */
	sc->bst = rman_get_bustag(sc->res[0]);
	sc->bsh = rman_get_bushandle(sc->res[0]);

	sc->iicbus = device_add_child(dev, "iicbus", -1);
	if (sc->iicbus == NULL) {
		device_printf(dev, "could not add iicbus child");
		mtx_destroy(&sc->mutex);
		return (ENXIO);
	}

	WRITE1(sc, I2CSTAT, 0);
	WRITE1(sc, I2CADD, 0x00);

	/* Mode */
	reg = (RXTX_EN);
        reg |= (I2CMODE_MT << I2CMODE_S);
	WRITE1(sc, I2CSTAT, reg);

	bus_generic_attach(dev);

	return (0);
}