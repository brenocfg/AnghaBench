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
struct ifnet {int if_flags; } ;
struct dc_softc {scalar_t__ suspended; struct ifnet* dc_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DC_LOCK (struct dc_softc*) ; 
 int /*<<< orphan*/  DC_UNLOCK (struct dc_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  dc_init_locked (struct dc_softc*) ; 
 struct dc_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
dc_resume(device_t dev)
{
	struct dc_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);
	ifp = sc->dc_ifp;

	/* reinitialize interface if necessary */
	DC_LOCK(sc);
	if (ifp->if_flags & IFF_UP)
		dc_init_locked(sc);

	sc->suspended = 0;
	DC_UNLOCK(sc);

	return (0);
}