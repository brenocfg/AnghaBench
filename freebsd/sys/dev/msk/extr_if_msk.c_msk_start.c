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
struct msk_if_softc {int dummy; } ;
struct ifnet {struct msk_if_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSK_IF_LOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  MSK_IF_UNLOCK (struct msk_if_softc*) ; 
 int /*<<< orphan*/  msk_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
msk_start(struct ifnet *ifp)
{
	struct msk_if_softc *sc_if;

	sc_if = ifp->if_softc;
	MSK_IF_LOCK(sc_if);
	msk_start_locked(ifp);
	MSK_IF_UNLOCK(sc_if);
}