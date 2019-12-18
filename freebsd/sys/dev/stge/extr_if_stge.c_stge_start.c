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
struct stge_softc {int dummy; } ;
struct ifnet {struct stge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  STGE_LOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  STGE_UNLOCK (struct stge_softc*) ; 
 int /*<<< orphan*/  stge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
stge_start(struct ifnet *ifp)
{
	struct stge_softc *sc;

	sc = ifp->if_softc;
	STGE_LOCK(sc);
	stge_start_locked(ifp);
	STGE_UNLOCK(sc);
}