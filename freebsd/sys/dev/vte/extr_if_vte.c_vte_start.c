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
struct vte_softc {int dummy; } ;
struct ifnet {struct vte_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  VTE_LOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_UNLOCK (struct vte_softc*) ; 
 int /*<<< orphan*/  vte_start_locked (struct vte_softc*) ; 

__attribute__((used)) static void
vte_start(struct ifnet *ifp)
{
	struct vte_softc *sc;

	sc = ifp->if_softc;
	VTE_LOCK(sc);
	vte_start_locked(sc);
	VTE_UNLOCK(sc);
}