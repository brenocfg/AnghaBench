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
struct ifnet {struct ale_softc* if_softc; } ;
struct ale_softc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_LOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ALE_UNLOCK (struct ale_softc*) ; 
 int /*<<< orphan*/  ale_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
ale_start(struct ifnet *ifp)
{
        struct ale_softc *sc;

	sc = ifp->if_softc;
	ALE_LOCK(sc);
	ale_start_locked(ifp);
	ALE_UNLOCK(sc);
}