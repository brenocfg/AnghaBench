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
struct ifaddr {int dummy; } ;
struct carp_softc {int sc_ifasiz; struct ifaddr** sc_ifas; } ;

/* Variables and functions */
 int /*<<< orphan*/  CARP_LOCK (struct carp_softc*) ; 
 int /*<<< orphan*/  CARP_UNLOCK (struct carp_softc*) ; 
 int /*<<< orphan*/  M_CARP ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  bcopy (struct ifaddr**,struct ifaddr**,int) ; 
 int /*<<< orphan*/  free (struct ifaddr**,int /*<<< orphan*/ ) ; 
 struct ifaddr** malloc (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
carp_grow_ifas(struct carp_softc *sc)
{
	struct ifaddr **new;

	new = malloc(sc->sc_ifasiz * 2, M_CARP, M_WAITOK | M_ZERO);
	CARP_LOCK(sc);
	bcopy(sc->sc_ifas, new, sc->sc_ifasiz);
	free(sc->sc_ifas, M_CARP);
	sc->sc_ifas = new;
	sc->sc_ifasiz *= 2;
	CARP_UNLOCK(sc);
}