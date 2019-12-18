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
struct mge_softc {int dummy; } ;
struct ifnet {struct mge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGE_TRANSMIT_LOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  MGE_TRANSMIT_UNLOCK (struct mge_softc*) ; 
 int /*<<< orphan*/  mge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
mge_start(struct ifnet *ifp)
{
	struct mge_softc *sc = ifp->if_softc;

	MGE_TRANSMIT_LOCK(sc);

	mge_start_locked(ifp);

	MGE_TRANSMIT_UNLOCK(sc);
}