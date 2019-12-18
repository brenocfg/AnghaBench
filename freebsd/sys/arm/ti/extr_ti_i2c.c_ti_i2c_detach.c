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
struct ti_i2c_softc {scalar_t__ sc_iicbus; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  TI_I2C_LOCK_DESTROY (struct ti_i2c_softc*) ; 
 int bus_generic_detach (int /*<<< orphan*/ ) ; 
 int device_delete_child (int /*<<< orphan*/ ,scalar_t__) ; 
 struct ti_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ti_i2c_deactivate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ti_i2c_detach(device_t dev)
{
	struct ti_i2c_softc *sc;
	int rv;

 	sc = device_get_softc(dev);

	if ((rv = bus_generic_detach(dev)) != 0) {
		device_printf(dev, "cannot detach child devices\n");
		return (rv);
	}

    if (sc->sc_iicbus &&
	    (rv = device_delete_child(dev, sc->sc_iicbus)) != 0)
		return (rv);

	ti_i2c_deactivate(dev);
	TI_I2C_LOCK_DESTROY(sc);

	return (0);
}