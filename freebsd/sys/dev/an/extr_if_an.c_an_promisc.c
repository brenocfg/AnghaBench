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
struct an_softc {scalar_t__ an_monitor; scalar_t__ an_was_monitor; scalar_t__ mpi350; } ;

/* Variables and functions */
 int /*<<< orphan*/  AN_CMD_SET_MODE ; 
 int /*<<< orphan*/  AN_LOCK_ASSERT (struct an_softc*) ; 
 int /*<<< orphan*/  an_cmd (struct an_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  an_init_locked (struct an_softc*) ; 
 int /*<<< orphan*/  an_init_mpi350_desc (struct an_softc*) ; 
 int /*<<< orphan*/  an_reset (struct an_softc*) ; 

__attribute__((used)) static void
an_promisc(struct an_softc *sc, int promisc)
{
	AN_LOCK_ASSERT(sc);
	if (sc->an_was_monitor) {
		an_reset(sc);
		if (sc->mpi350)
			an_init_mpi350_desc(sc);
	}
	if (sc->an_monitor || sc->an_was_monitor)
		an_init_locked(sc);

	sc->an_was_monitor = sc->an_monitor;
	an_cmd(sc, AN_CMD_SET_MODE, promisc ? 0xffff : 0);

	return;
}