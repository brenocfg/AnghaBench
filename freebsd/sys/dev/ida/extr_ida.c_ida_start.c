#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* submit ) (struct ida_softc*,struct ida_qcb*) ;scalar_t__ (* fifo_full ) (struct ida_softc*) ;} ;
struct ida_softc {TYPE_1__ cmd; int /*<<< orphan*/  qactive; int /*<<< orphan*/  ch; int /*<<< orphan*/  qcb_queue; int /*<<< orphan*/  lock; } ;
struct ida_qcb {int /*<<< orphan*/  state; } ;
struct TYPE_4__ {int /*<<< orphan*/  stqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  QCB_ACTIVE ; 
 struct ida_qcb* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,struct ida_softc*) ; 
 int /*<<< orphan*/  dumping ; 
 int hz ; 
 int /*<<< orphan*/  ida_timeout ; 
 TYPE_2__ link ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct ida_softc*) ; 
 int /*<<< orphan*/  stub2 (struct ida_softc*,struct ida_qcb*) ; 

__attribute__((used)) static void
ida_start(struct ida_softc *ida)
{
	struct ida_qcb *qcb;

	if (!dumping)
		mtx_assert(&ida->lock, MA_OWNED);
	while ((qcb = STAILQ_FIRST(&ida->qcb_queue)) != NULL) {
		if (ida->cmd.fifo_full(ida))
			break;
		STAILQ_REMOVE_HEAD(&ida->qcb_queue, link.stqe);
		/*
		 * XXX
		 * place the qcb on an active list?
		 */

		/* Set a timeout. */
		if (!ida->qactive && !dumping)
			callout_reset(&ida->ch, hz * 5, ida_timeout, ida);
		ida->qactive++;

		qcb->state = QCB_ACTIVE;
		ida->cmd.submit(ida, qcb);
	}
}