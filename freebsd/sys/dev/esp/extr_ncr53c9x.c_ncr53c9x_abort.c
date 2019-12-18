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
struct ncr53c9x_softc {scalar_t__ sc_state; struct ncr53c9x_ecb* sc_nexus; } ;
struct ncr53c9x_ecb {int /*<<< orphan*/  timeout; int /*<<< orphan*/  ch; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECB_ABORT ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NCR_ABORT_TIMEOUT ; 
 scalar_t__ NCR_CONNECTED ; 
 scalar_t__ NCR_IDLE ; 
 int /*<<< orphan*/  NCR_LOCK_ASSERT (struct ncr53c9x_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SEND_ABORT ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ncr53c9x_ecb*) ; 
 int /*<<< orphan*/  mstohz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ncr53c9x_callout ; 
 int /*<<< orphan*/  ncr53c9x_sched (struct ncr53c9x_softc*) ; 
 int /*<<< orphan*/  ncr53c9x_sched_msgout (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ncr53c9x_abort(struct ncr53c9x_softc *sc, struct ncr53c9x_ecb *ecb)
{

	NCR_LOCK_ASSERT(sc, MA_OWNED);

	/* 2 secs for the abort */
	ecb->timeout = NCR_ABORT_TIMEOUT;
	ecb->flags |= ECB_ABORT;

	if (ecb == sc->sc_nexus) {
		/*
		 * If we're still selecting, the message will be scheduled
		 * after selection is complete.
		 */
		if (sc->sc_state == NCR_CONNECTED)
			ncr53c9x_sched_msgout(SEND_ABORT);

		/*
		 * Reschedule callout.
		 */
		callout_reset(&ecb->ch, mstohz(ecb->timeout),
		    ncr53c9x_callout, ecb);
	} else {
		/*
		 * Just leave the command where it is.
		 * XXX - what choice do we have but to reset the SCSI
		 *	 eventually?
		 */
		if (sc->sc_state == NCR_IDLE)
			ncr53c9x_sched(sc);
	}
}