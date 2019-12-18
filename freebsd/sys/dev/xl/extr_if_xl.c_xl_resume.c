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
struct xl_softc {struct ifnet* xl_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  XL_LOCK (struct xl_softc*) ; 
 int /*<<< orphan*/  XL_UNLOCK (struct xl_softc*) ; 
 struct xl_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xl_init_locked (struct xl_softc*) ; 

__attribute__((used)) static int
xl_resume(device_t dev)
{
	struct xl_softc		*sc;
	struct ifnet		*ifp;

	sc = device_get_softc(dev);
	ifp = sc->xl_ifp;

	XL_LOCK(sc);

	if (ifp->if_flags & IFF_UP) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		xl_init_locked(sc);
	}

	XL_UNLOCK(sc);

	return (0);
}