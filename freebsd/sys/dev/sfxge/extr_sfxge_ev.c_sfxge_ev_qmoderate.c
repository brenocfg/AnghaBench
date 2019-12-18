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
struct sfxge_softc {struct sfxge_evq** evq; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/ * common; } ;
typedef  int /*<<< orphan*/  efx_evq_t ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 int /*<<< orphan*/  efx_ev_qmoderate (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static void
sfxge_ev_qmoderate(struct sfxge_softc *sc, unsigned int idx, unsigned int us)
{
	struct sfxge_evq *evq;
	efx_evq_t *eep;

	evq = sc->evq[idx];
	eep = evq->common;

	KASSERT(evq->init_state == SFXGE_EVQ_STARTED,
	    ("evq->init_state != SFXGE_EVQ_STARTED"));

	(void)efx_ev_qmoderate(eep, us);
}