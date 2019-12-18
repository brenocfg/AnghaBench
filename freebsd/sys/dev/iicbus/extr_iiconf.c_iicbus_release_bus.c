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
struct iicbus_softc {scalar_t__ owner; scalar_t__ owncount; int /*<<< orphan*/  busydev; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IICBUS_CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IICBUS_LOCK (struct iicbus_softc*) ; 
 int /*<<< orphan*/  IICBUS_UNLOCK (struct iicbus_softc*) ; 
 int IIC_EBUSBSY ; 
 int /*<<< orphan*/  IIC_RELEASE_BUS ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 scalar_t__ device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  device_unbusy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup_one (struct iicbus_softc*) ; 

int
iicbus_release_bus(device_t bus, device_t dev)
{
	struct iicbus_softc *sc = (struct iicbus_softc *)device_get_softc(bus);

	IICBUS_LOCK(sc);

	if (sc->owner != dev) {
		IICBUS_UNLOCK(sc);
		return (IIC_EBUSBSY);
	}

	if (--sc->owncount == 0) {
		/* Drop the lock while informing the low-level driver. */
		IICBUS_UNLOCK(sc);
		IICBUS_CALLBACK(device_get_parent(bus), IIC_RELEASE_BUS, NULL);
		IICBUS_LOCK(sc);
		sc->owner = NULL;
		wakeup_one(sc);
		device_unbusy(sc->busydev);
	}
	IICBUS_UNLOCK(sc);
	return (0);
}