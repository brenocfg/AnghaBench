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
struct sbni_softc {int /*<<< orphan*/  wch; struct ifnet* ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_OACTIVE ; 
 int IFF_DRV_RUNNING ; 
 int SBNI_HZ ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct sbni_softc*) ; 
 int /*<<< orphan*/  card_start (struct sbni_softc*) ; 
 int hz ; 
 int /*<<< orphan*/  sbni_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  sbni_timeout ; 

__attribute__((used)) static void
sbni_init_locked(struct sbni_softc *sc)
{
	struct ifnet *ifp;

	ifp = sc->ifp;

	/*
	 * kludge to avoid multiple initialization when more than once
	 * protocols configured
	 */
	if (ifp->if_drv_flags & IFF_DRV_RUNNING)
		return;

	card_start(sc);
	callout_reset(&sc->wch, hz/SBNI_HZ, sbni_timeout, sc);

	ifp->if_drv_flags |= IFF_DRV_RUNNING;
	ifp->if_drv_flags &= ~IFF_DRV_OACTIVE;

	/* attempt to start output */
	sbni_start_locked(ifp);
}