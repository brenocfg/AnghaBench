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
struct age_softc {struct ifnet* age_ifp; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  AGE_LOCK (struct age_softc*) ; 
 int /*<<< orphan*/  AGE_UNLOCK (struct age_softc*) ; 
 int IFF_UP ; 
 int /*<<< orphan*/  age_init_locked (struct age_softc*) ; 
 int /*<<< orphan*/  age_phy_reset (struct age_softc*) ; 
 struct age_softc* device_get_softc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
age_resume(device_t dev)
{
	struct age_softc *sc;
	struct ifnet *ifp;

	sc = device_get_softc(dev);

	AGE_LOCK(sc);
	age_phy_reset(sc);
	ifp = sc->age_ifp;
	if ((ifp->if_flags & IFF_UP) != 0)
		age_init_locked(sc);

	AGE_UNLOCK(sc);

	return (0);
}