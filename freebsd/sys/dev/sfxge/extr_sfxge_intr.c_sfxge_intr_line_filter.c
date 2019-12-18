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
typedef  scalar_t__ uint32_t ;
struct sfxge_intr {scalar_t__ type; scalar_t__ state; scalar_t__ zero_count; } ;
struct sfxge_softc {struct sfxge_intr intr; int /*<<< orphan*/ * enp; } ;
struct sfxge_evq {scalar_t__ init_state; int /*<<< orphan*/  read_ptr; int /*<<< orphan*/  common; struct sfxge_softc* sc; } ;
typedef  int /*<<< orphan*/  efx_nic_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ EFX_INTR_LINE ; 
 int FILTER_HANDLED ; 
 int FILTER_SCHEDULE_THREAD ; 
 int FILTER_STRAY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ SFXGE_EVQ_STARTED ; 
 scalar_t__ SFXGE_INTR_STARTED ; 
 scalar_t__ efx_ev_qpending (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_ev_qprime (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efx_intr_disable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_intr_fatal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efx_intr_status_line (int /*<<< orphan*/ *,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static int
sfxge_intr_line_filter(void *arg)
{
	struct sfxge_evq *evq;
	struct sfxge_softc *sc;
	efx_nic_t *enp;
	struct sfxge_intr *intr;
	boolean_t fatal;
	uint32_t qmask;

	evq = (struct sfxge_evq *)arg;
	sc = evq->sc;
	enp = sc->enp;
	intr = &sc->intr;

	KASSERT(intr != NULL, ("intr == NULL"));
	KASSERT(intr->type == EFX_INTR_LINE,
	    ("intr->type != EFX_INTR_LINE"));

	if (intr->state != SFXGE_INTR_STARTED)
		return (FILTER_STRAY);

	(void)efx_intr_status_line(enp, &fatal, &qmask);

	if (fatal) {
		(void) efx_intr_disable(enp);
		(void) efx_intr_fatal(enp);
		return (FILTER_HANDLED);
	}

	if (qmask != 0) {
		intr->zero_count = 0;
		return (FILTER_SCHEDULE_THREAD);
	}

	/* SF bug 15783: If the function is not asserting its IRQ and
	 * we read the queue mask on the cycle before a flag is added
	 * to the mask, this inhibits the function from asserting the
	 * IRQ even though we don't see the flag set.  To work around
	 * this, we must re-prime all event queues and report the IRQ
	 * as handled when we see a mask of zero.  To allow for shared
	 * IRQs, we don't repeat this if we see a mask of zero twice
	 * or more in a row.
	 */
	if (intr->zero_count++ == 0) {
		if (evq->init_state == SFXGE_EVQ_STARTED) {
			if (efx_ev_qpending(evq->common, evq->read_ptr))
				return (FILTER_SCHEDULE_THREAD);
			efx_ev_qprime(evq->common, evq->read_ptr);
			return (FILTER_HANDLED);
		}
	}

	return (FILTER_STRAY);
}