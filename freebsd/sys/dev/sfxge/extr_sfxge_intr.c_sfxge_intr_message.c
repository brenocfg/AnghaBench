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
struct sfxge_intr {scalar_t__ type; scalar_t__ state; } ;
struct sfxge_softc {struct sfxge_intr intr; int /*<<< orphan*/ * enp; } ;
struct sfxge_evq {unsigned int index; struct sfxge_softc* sc; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ EFX_INTR_MESSAGE ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_INTR_STARTED ; 
 scalar_t__ __predict_false (int) ; 
 int /*<<< orphan*/  efx_intr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_intr_fatal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_intr_status_message (int /*<<< orphan*/ *,unsigned int,scalar_t__*) ; 
 int /*<<< orphan*/  sfxge_ev_qpoll (struct sfxge_evq*) ; 

__attribute__((used)) static void
sfxge_intr_message(void *arg)
{
	struct sfxge_evq *evq;
	struct sfxge_softc *sc;
	efx_nic_t *enp;
	struct sfxge_intr *intr;
	unsigned int index;
	boolean_t fatal;

	evq = (struct sfxge_evq *)arg;
	sc = evq->sc;
	enp = sc->enp;
	intr = &sc->intr;
	index = evq->index;

	KASSERT(intr != NULL, ("intr == NULL"));
	KASSERT(intr->type == EFX_INTR_MESSAGE,
	    ("intr->type != EFX_INTR_MESSAGE"));

	if (__predict_false(intr->state != SFXGE_INTR_STARTED))
		return;

	(void)efx_intr_status_message(enp, index, &fatal);

	if (fatal) {
		(void)efx_intr_disable(enp);
		(void)efx_intr_fatal(enp);
		return;
	}

	(void)sfxge_ev_qpoll(evq);
}