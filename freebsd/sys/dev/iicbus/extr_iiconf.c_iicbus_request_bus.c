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
struct iicbus_softc {void* owner; void* busydev; scalar_t__ owncount; } ;
typedef  void* device_t ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ DS_ATTACHING ; 
 int IICBUS_CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IICBUS_LOCK (struct iicbus_softc*) ; 
 int /*<<< orphan*/  IICBUS_UNLOCK (struct iicbus_softc*) ; 
 int IIC_RECURSIVE ; 
 int /*<<< orphan*/  IIC_REQUEST_BUS ; 
 int /*<<< orphan*/  device_busy (void*) ; 
 int /*<<< orphan*/  device_get_parent (void*) ; 
 scalar_t__ device_get_softc (void*) ; 
 scalar_t__ device_get_state (void*) ; 
 int /*<<< orphan*/  device_unbusy (void*) ; 
 int iicbus_poll (struct iicbus_softc*,int) ; 
 int /*<<< orphan*/  wakeup_one (struct iicbus_softc*) ; 

int
iicbus_request_bus(device_t bus, device_t dev, int how)
{
	struct iicbus_softc *sc = (struct iicbus_softc *)device_get_softc(bus);
	int error = 0;

	IICBUS_LOCK(sc);

	for (;;) {
		if (sc->owner == NULL)
			break;
		if ((how & IIC_RECURSIVE) && sc->owner == dev)
			break;
		if ((error = iicbus_poll(sc, how)) != 0)
			break;
	}

	if (error == 0) {
		++sc->owncount;
		if (sc->owner == NULL) {
			sc->owner = dev;
			/*
			 * Mark the device busy while it owns the bus, to
			 * prevent detaching the device, bus, or hardware
			 * controller, until ownership is relinquished.  If the
			 * device is doing IO from its probe method before
			 * attaching, it cannot be busied; mark the bus busy.
			 */
			if (device_get_state(dev) < DS_ATTACHING)
				sc->busydev = bus;
			else
				sc->busydev = dev;
			device_busy(sc->busydev);
			/* 
			 * Drop the lock around the call to the bus driver, it
			 * should be allowed to sleep in the IIC_WAIT case.
			 * Drivers might also need to grab locks that would
			 * cause a LOR if our lock is held.
			 */
			IICBUS_UNLOCK(sc);
			/* Ask the underlying layers if the request is ok */
			error = IICBUS_CALLBACK(device_get_parent(bus),
			    IIC_REQUEST_BUS, (caddr_t)&how);
			IICBUS_LOCK(sc);
	
			if (error != 0) {
				sc->owner = NULL;
				sc->owncount = 0;
				wakeup_one(sc);
				device_unbusy(sc->busydev);
			}
		}
	}

	IICBUS_UNLOCK(sc);

	return (error);
}