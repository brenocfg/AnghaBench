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
struct sis_softc {struct ifnet* sis_ifp; } ;
struct ifnet {int if_flags; int /*<<< orphan*/  if_drv_flags; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_DRV_RUNNING ; 
 int IFF_UP ; 
 int /*<<< orphan*/  SIS_LOCK (struct sis_softc*) ; 
 int /*<<< orphan*/  SIS_UNLOCK (struct sis_softc*) ; 
 struct sis_softc* device_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sis_initl (struct sis_softc*) ; 

__attribute__((used)) static int
sis_resume(device_t dev)
{
	struct sis_softc	*sc;
	struct ifnet		*ifp;

	sc = device_get_softc(dev);
	SIS_LOCK(sc);
	ifp = sc->sis_ifp;
	if ((ifp->if_flags & IFF_UP) != 0) {
		ifp->if_drv_flags &= ~IFF_DRV_RUNNING;
		sis_initl(sc);
	}
	SIS_UNLOCK(sc);
	return (0);
}