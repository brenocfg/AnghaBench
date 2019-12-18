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
struct ifnet {struct glc_softc* if_softc; } ;
struct glc_softc {int /*<<< orphan*/  sc_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  glc_start_locked (struct ifnet*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
glc_start(struct ifnet *ifp)
{
	struct glc_softc *sc = ifp->if_softc;

	mtx_lock(&sc->sc_mtx);
	glc_start_locked(ifp);
	mtx_unlock(&sc->sc_mtx);
}