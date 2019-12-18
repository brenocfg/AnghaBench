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
struct ifnet {struct dme_softc* if_softc; } ;
struct dme_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DME_LOCK (struct dme_softc*) ; 
 int /*<<< orphan*/  DME_UNLOCK (struct dme_softc*) ; 
 int /*<<< orphan*/  dme_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
dme_start(struct ifnet *ifp)
{
	struct dme_softc *sc;

	sc = ifp->if_softc;
	DME_LOCK(sc);
	dme_start_locked(ifp);
	DME_UNLOCK(sc);
}