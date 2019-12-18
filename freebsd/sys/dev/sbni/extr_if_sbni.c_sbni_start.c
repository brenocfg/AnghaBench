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
struct sbni_softc {int dummy; } ;
struct ifnet {struct sbni_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  SBNI_LOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  SBNI_UNLOCK (struct sbni_softc*) ; 
 int /*<<< orphan*/  sbni_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
sbni_start(struct ifnet *ifp)
{
	struct sbni_softc *sc = ifp->if_softc;

	SBNI_LOCK(sc);
	sbni_start_locked(ifp);
	SBNI_UNLOCK(sc);
}