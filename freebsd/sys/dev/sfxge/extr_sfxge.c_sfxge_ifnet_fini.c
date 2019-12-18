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
struct sfxge_softc {int /*<<< orphan*/  media; } ;
struct ifnet {struct sfxge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SFXGE_ADAPTER_LOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  SFXGE_ADAPTER_UNLOCK (struct sfxge_softc*) ; 
 int /*<<< orphan*/  ether_ifdetach (struct ifnet*) ; 
 int /*<<< orphan*/  if_free (struct ifnet*) ; 
 int /*<<< orphan*/  ifmedia_removeall (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_stop (struct sfxge_softc*) ; 

__attribute__((used)) static void
sfxge_ifnet_fini(struct ifnet *ifp)
{
	struct sfxge_softc *sc = ifp->if_softc;

	SFXGE_ADAPTER_LOCK(sc);
	sfxge_stop(sc);
	SFXGE_ADAPTER_UNLOCK(sc);

	ifmedia_removeall(&sc->media);
	ether_ifdetach(ifp);
	if_free(ifp);
}