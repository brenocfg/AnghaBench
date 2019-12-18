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
typedef  int /*<<< orphan*/  u_char ;
struct smbus_softc {int /*<<< orphan*/  lock; scalar_t__ owner; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  SMBUS_INTR (scalar_t__,int /*<<< orphan*/ ,char,char,int) ; 
 struct smbus_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

void
smbus_intr(device_t bus, u_char devaddr, char low, char high, int error)
{
	struct smbus_softc *sc = device_get_softc(bus);

	/* call owner's intr routine */
	mtx_lock(&sc->lock);
	if (sc->owner)
		SMBUS_INTR(sc->owner, devaddr, low, high, error);
	mtx_unlock(&sc->lock);
}