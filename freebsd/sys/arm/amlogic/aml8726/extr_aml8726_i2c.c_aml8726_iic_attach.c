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
struct aml8726_iic_softc {int /*<<< orphan*/  res; int /*<<< orphan*/ * iicbb; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AML_I2C_LOCK_DESTROY (struct aml8726_iic_softc*) ; 
 int /*<<< orphan*/  AML_I2C_LOCK_INIT (struct aml8726_iic_softc*) ; 
 int ENXIO ; 
 int /*<<< orphan*/  aml8726_iic_spec ; 
 scalar_t__ bus_alloc_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_release_resources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * device_add_child (int /*<<< orphan*/ ,char*,int) ; 
 struct aml8726_iic_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int device_probe_and_attach (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
aml8726_iic_attach(device_t dev)
{
	struct aml8726_iic_softc *sc = device_get_softc(dev);
	int error;

	sc->dev = dev;

	if (bus_alloc_resources(dev, aml8726_iic_spec, sc->res)) {
		device_printf(dev, "can not allocate resources for device\n");
		return (ENXIO);
	}

	AML_I2C_LOCK_INIT(sc);

	sc->iicbb = device_add_child(dev, "iicbb", -1);

	if (sc->iicbb == NULL) {
		device_printf(dev, "could not add iicbb\n");
		error = ENXIO;
		goto fail;
	}

	error = device_probe_and_attach(sc->iicbb);

	if (error) {
		device_printf(dev, "could not attach iicbb\n");
		goto fail;
	}

	return (0);

fail:
	AML_I2C_LOCK_DESTROY(sc);
	bus_release_resources(dev, aml8726_iic_spec, sc->res);

	return (error);
}