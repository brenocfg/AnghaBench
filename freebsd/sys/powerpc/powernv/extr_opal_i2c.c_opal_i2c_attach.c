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
struct opal_i2c_softc {int /*<<< orphan*/ * iicbus; int /*<<< orphan*/  opal_id; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  I2C_LOCK_INIT (struct opal_i2c_softc*) ; 
 int /*<<< orphan*/  OF_getencprop (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int) ; 
 int OF_getproplen (int /*<<< orphan*/ ,char*) ; 
 int bus_generic_attach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct opal_i2c_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ofw_bus_get_node (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
opal_i2c_attach(device_t dev)
{
	struct opal_i2c_softc *sc;
	int len;

	sc = device_get_softc(dev);
	sc->dev = dev;

	len = OF_getproplen(ofw_bus_get_node(dev), "ibm,opal-id");
	if (len <= 0)
		return (EINVAL);
	OF_getencprop(ofw_bus_get_node(dev), "ibm,opal-id", &sc->opal_id, len);

	if ((sc->iicbus = device_add_child(dev, "iicbus", -1)) == NULL) {
		device_printf(dev, "could not allocate iicbus instance\n");
		return (EINVAL);
	}

	I2C_LOCK_INIT(sc);

	return (bus_generic_attach(dev));
}