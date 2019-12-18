#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct lance_softc {TYPE_1__* sc_ifp; } ;
struct TYPE_2__ {int if_flags; } ;

/* Variables and functions */
 int IFF_UP ; 
 int /*<<< orphan*/  LE_LOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  LE_UNLOCK (struct lance_softc*) ; 
 int /*<<< orphan*/  lance_init_locked (struct lance_softc*) ; 

void
lance_resume(struct lance_softc *sc)
{

	LE_LOCK(sc);
	if (sc->sc_ifp->if_flags & IFF_UP)
		lance_init_locked(sc);
	LE_UNLOCK(sc);
}