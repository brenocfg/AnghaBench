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
struct sfxge_intr {scalar_t__ state; } ;
struct sfxge_softc {int evq_count; int /*<<< orphan*/  enp; struct sfxge_intr intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_INTR_STARTED ; 
 int /*<<< orphan*/  efx_ev_fini (int /*<<< orphan*/ ) ; 
 int efx_ev_init (int /*<<< orphan*/ ) ; 
 int sfxge_ev_qstart (struct sfxge_softc*,int) ; 
 int /*<<< orphan*/  sfxge_ev_qstop (struct sfxge_softc*,int) ; 

int
sfxge_ev_start(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;
	int index;
	int rc;

	intr = &sc->intr;

	KASSERT(intr->state == SFXGE_INTR_STARTED,
	    ("intr->state != SFXGE_INTR_STARTED"));

	/* Initialize the event module */
	if ((rc = efx_ev_init(sc->enp)) != 0)
		return (rc);

	/* Start the event queues */
	for (index = 0; index < sc->evq_count; index++) {
		if ((rc = sfxge_ev_qstart(sc, index)) != 0)
			goto fail;
	}

	return (0);

fail:
	/* Stop the event queue(s) */
	while (--index >= 0)
		sfxge_ev_qstop(sc, index);

	/* Tear down the event module */
	efx_ev_fini(sc->enp);

	return (rc);
}