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
typedef  int uint8_t ;
struct adt746x_softc {int device_id; int /*<<< orphan*/  enum_hook; int /*<<< orphan*/  sc_addr; int /*<<< orphan*/  sc_dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ADT7460_DEV_ID ; 
 int /*<<< orphan*/  ADT746X_COMPANY_ID ; 
 int /*<<< orphan*/  ADT746X_CONFIG ; 
 int /*<<< orphan*/  ADT746X_DEVICE_ID ; 
 int /*<<< orphan*/  ADT746X_REV_ID ; 
 int /*<<< orphan*/  adt746x_attach_fans (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt746x_attach_sensors (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  adt746x_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  adt746x_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  config_intrhook_disestablish (int /*<<< orphan*/ *) ; 
 struct adt746x_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int,int,int,int) ; 

__attribute__((used)) static void
adt746x_start(void *xdev)
{
	uint8_t did, cid, rev, conf;

	struct adt746x_softc *sc;

	device_t dev = (device_t)xdev;

	sc = device_get_softc(dev);

	adt746x_read(sc->sc_dev, sc->sc_addr, ADT746X_DEVICE_ID, &did);
	adt746x_read(sc->sc_dev, sc->sc_addr, ADT746X_COMPANY_ID, &cid);
	adt746x_read(sc->sc_dev, sc->sc_addr, ADT746X_REV_ID, &rev);
	adt746x_read(sc->sc_dev, sc->sc_addr, ADT746X_CONFIG, &conf);

	device_printf(dev, "Dev ID %#x, Company ID %#x, Rev ID %#x CNF: %#x\n",
		      did, cid, rev, conf);

	/* We can get the device id either from 'of' properties or from the chip
	   itself. This method makes sure we can read the chip, otherwise
	   we return.  */

	sc->device_id = did;

	conf = 1;
	/* Start the ADT7460.  */
	if (sc->device_id == ADT7460_DEV_ID)
		adt746x_write(sc->sc_dev, sc->sc_addr, ADT746X_CONFIG, &conf);

	/* Detect and attach child devices.  */
	adt746x_attach_fans(dev);
	adt746x_attach_sensors(dev);
	config_intrhook_disestablish(&sc->enum_hook);
}