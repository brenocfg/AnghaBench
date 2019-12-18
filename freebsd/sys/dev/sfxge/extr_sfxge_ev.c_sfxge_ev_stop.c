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
struct sfxge_softc {int evq_count; int /*<<< orphan*/ * enp; struct sfxge_intr intr; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_INTR_STARTED ; 
 int /*<<< orphan*/  efx_ev_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sfxge_ev_qstop (struct sfxge_softc*,int) ; 

void
sfxge_ev_stop(struct sfxge_softc *sc)
{
	struct sfxge_intr *intr;
	efx_nic_t *enp;
	int index;

	intr = &sc->intr;
	enp = sc->enp;

	KASSERT(intr->state == SFXGE_INTR_STARTED,
	    ("Interrupts not started"));

	/* Stop the event queue(s) */
	index = sc->evq_count;
	while (--index >= 0)
		sfxge_ev_qstop(sc, index);

	/* Tear down the event module */
	efx_ev_fini(enp);
}