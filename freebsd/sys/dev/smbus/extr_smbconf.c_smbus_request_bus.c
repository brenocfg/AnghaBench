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
struct smbus_softc {scalar_t__ owner; int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ device_t ;

/* Variables and functions */
 int EWOULDBLOCK ; 
 int SMBUS_CALLBACK (scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  SMB_RELEASE_BUS ; 
 int /*<<< orphan*/  SMB_REQUEST_BUS ; 
 scalar_t__ device_get_parent (scalar_t__) ; 
 struct smbus_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int smbus_poll (struct smbus_softc*,int) ; 

int
smbus_request_bus(device_t bus, device_t dev, int how)
{
	struct smbus_softc *sc = device_get_softc(bus);
	device_t parent;
	int error;

	/* first, ask the underlying layers if the request is ok */
	parent = device_get_parent(bus);
	mtx_lock(&sc->lock);
	do {
		mtx_unlock(&sc->lock);
		error = SMBUS_CALLBACK(parent, SMB_REQUEST_BUS, &how);
		mtx_lock(&sc->lock);

		if (error)
			error = smbus_poll(sc, how);
	} while (error == EWOULDBLOCK);

	while (error == 0) {
		if (sc->owner && sc->owner != dev)
			error = smbus_poll(sc, how);
		else {
			sc->owner = dev;
			break;
		}

		/* free any allocated resource */
		if (error) {
			mtx_unlock(&sc->lock);
			SMBUS_CALLBACK(parent, SMB_RELEASE_BUS, &how);
			return (error);
		}
	}
	mtx_unlock(&sc->lock);

	return (error);
}