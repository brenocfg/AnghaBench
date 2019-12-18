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
struct llan_softc {int /*<<< orphan*/  io_lock; } ;
struct ifnet {struct llan_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  llan_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
llan_start(struct ifnet *ifp)
{
	struct llan_softc *sc = ifp->if_softc;

	mtx_lock(&sc->io_lock);
	llan_start_locked(ifp);
	mtx_unlock(&sc->io_lock);
}