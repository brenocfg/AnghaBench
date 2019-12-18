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
struct lance_softc {int /*<<< orphan*/  (* sc_start_locked ) (struct lance_softc*) ;} ;
struct ifnet {struct lance_softc* if_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  LE_LOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_UNLOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  stub1 (struct lance_softc*) ; 

__attribute__((used)) static void
lance_start(struct ifnet *ifp)
{
	struct lance_softc *sc = ifp->if_softc;

	LE_LOCK(sc);
	(*sc->sc_start_locked)(sc);
	LE_UNLOCK(sc);
}