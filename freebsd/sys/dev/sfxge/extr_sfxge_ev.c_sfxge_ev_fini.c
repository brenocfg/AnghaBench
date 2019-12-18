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
struct sfxge_softc {int evq_count; scalar_t__ ev_moderation; struct sfxge_intr intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_INTR_INITIALIZED ; 
 int /*<<< orphan*/  sfxge_ev_qfini (struct sfxge_softc*,int) ; 

void
sfxge_ev_fini(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;
	int index;

	intr = &sc->intr;

	KASSERT(intr->state == SFXGE_INTR_INITIALIZED,
	    ("intr->state != SFXGE_INTR_INITIALIZED"));

	sc->ev_moderation = 0;

	/* Tear down the event queue(s). */
	index = sc->evq_count;
	while (--index >= 0)
		sfxge_ev_qfini(sc, index);

	sc->evq_count = 0;
}