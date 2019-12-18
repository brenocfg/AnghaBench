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
struct nge_softc {int dummy; } ;
struct ifnet {struct nge_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGE_LOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  NGE_UNLOCK (struct nge_softc*) ; 
 int /*<<< orphan*/  nge_start_locked (struct ifnet*) ; 

__attribute__((used)) static void
nge_start(struct ifnet *ifp)
{
	struct nge_softc *sc;

	sc = ifp->if_softc;
	NGE_LOCK(sc);
	nge_start_locked(ifp);
	NGE_UNLOCK(sc);
}