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
 int EACCES ; 
 int SMBUS_CALLBACK (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SMB_RELEASE_BUS ; 
 int /*<<< orphan*/  device_get_parent (scalar_t__) ; 
 struct smbus_softc* device_get_softc (scalar_t__) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct smbus_softc*) ; 

int
smbus_release_bus(device_t bus, device_t dev)
{
	struct smbus_softc *sc = device_get_softc(bus);
	int error;

	/* first, ask the underlying layers if the release is ok */
	error = SMBUS_CALLBACK(device_get_parent(bus), SMB_RELEASE_BUS, NULL);

	if (error)
		return (error);

	mtx_lock(&sc->lock);
	if (sc->owner == dev) {
		sc->owner = NULL;

		/* wakeup waiting processes */
		wakeup(sc);
	} else
		error = EACCES;
	mtx_unlock(&sc->lock);

	return (error);
}