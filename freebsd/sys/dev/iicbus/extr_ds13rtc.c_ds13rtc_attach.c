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
struct ds13rtc_softc {int chiptype; int use_century; int is_binary_counter; void* osfaddr; void* secaddr; int /*<<< orphan*/  busdev; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 void* DS133x_R_STATUS ; 
 void* DS1340_R_STATUS ; 
 void* DS137x_R_STATUS ; 
 void* DS1388_R_SECOND ; 
 void* DS1388_R_STATUS ; 
 void* DS13xx_R_SECOND ; 
 int ENXIO ; 
#define  TYPE_DS1307 140 
#define  TYPE_DS1308 139 
#define  TYPE_DS1337 138 
#define  TYPE_DS1338 137 
#define  TYPE_DS1339 136 
#define  TYPE_DS1340 135 
#define  TYPE_DS1341 134 
#define  TYPE_DS1342 133 
#define  TYPE_DS1371 132 
#define  TYPE_DS1372 131 
#define  TYPE_DS1374 130 
#define  TYPE_DS1375 129 
#define  TYPE_DS1388 128 
 int TYPE_NONE ; 
 int /*<<< orphan*/  config_intrhook_oneshot (int /*<<< orphan*/ ,struct ds13rtc_softc*) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct ds13rtc_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int ds13rtc_get_chiptype (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ds13rtc_start ; 

__attribute__((used)) static int
ds13rtc_attach(device_t dev)
{
	struct ds13rtc_softc *sc;

	sc = device_get_softc(dev);
	sc->dev = dev;
	sc->busdev = device_get_parent(dev);

	/*
	 * We need to know what kind of chip we're driving.
	 */
	if ((sc->chiptype = ds13rtc_get_chiptype(dev)) == TYPE_NONE) {
		device_printf(dev, "impossible: cannot determine chip type\n");
		return (ENXIO);
	}

	/* The seconds register is in the same place on all except DS1388. */
	if (sc->chiptype == TYPE_DS1388) 
		sc->secaddr = DS1388_R_SECOND;
	else
		sc->secaddr = DS13xx_R_SECOND;

	/*
	 * The OSF/CH (osc failed/clock-halted) bit appears in different
	 * registers for different chip types.  The DS1375 has no OSF indicator
	 * because it has no internal oscillator; we just point to an always-
	 * zero bit in the status register for that chip.
	 */
	switch (sc->chiptype) {
	case TYPE_DS1307:
	case TYPE_DS1308:
	case TYPE_DS1338:
		sc->osfaddr = DS13xx_R_SECOND;
		break;
	case TYPE_DS1337:
	case TYPE_DS1339:
	case TYPE_DS1341:
	case TYPE_DS1342:
	case TYPE_DS1375:
		sc->osfaddr = DS133x_R_STATUS;
		sc->use_century = true;
		break;
	case TYPE_DS1340:
		sc->osfaddr = DS1340_R_STATUS;
		break;
	case TYPE_DS1371:
	case TYPE_DS1372:
	case TYPE_DS1374:
		sc->osfaddr = DS137x_R_STATUS;
		sc->is_binary_counter = true;
		break;
	case TYPE_DS1388:
		sc->osfaddr = DS1388_R_STATUS;
		break;
	}

	/*
	 * We have to wait until interrupts are enabled.  Sometimes I2C read
	 * and write only works when the interrupts are available.
	 */
	config_intrhook_oneshot(ds13rtc_start, sc);

	return (0);
}