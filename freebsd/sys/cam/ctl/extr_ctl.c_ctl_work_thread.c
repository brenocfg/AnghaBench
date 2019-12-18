#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ io_type; } ;
union ctl_io {int /*<<< orphan*/  scsiio; TYPE_1__ io_hdr; } ;
struct ctl_thread {int /*<<< orphan*/ * thread; int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  rtr_queue; int /*<<< orphan*/  incoming_queue; int /*<<< orphan*/  done_queue; int /*<<< orphan*/  isc_queue; struct ctl_softc* ctl_softc; } ;
struct ctl_softc {int /*<<< orphan*/  shutdown; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTL_DEBUG_PRINT (char*) ; 
 scalar_t__ CTL_IO_TASK ; 
 int CTL_RETVAL_COMPLETE ; 
 int /*<<< orphan*/  PDROP ; 
 scalar_t__ PUSER ; 
 scalar_t__ STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE_HEAD (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ctl_handle_isc (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_process_done (union ctl_io*) ; 
 int /*<<< orphan*/  ctl_run_task (union ctl_io*) ; 
 int ctl_scsiio (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctl_scsiio_precheck (struct ctl_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curthread ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_sleep (struct ctl_thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ctl_work_thread(void *arg)
{
	struct ctl_thread *thr = (struct ctl_thread *)arg;
	struct ctl_softc *softc = thr->ctl_softc;
	union ctl_io *io;
	int retval;

	CTL_DEBUG_PRINT(("ctl_work_thread starting\n"));
	thread_lock(curthread);
	sched_prio(curthread, PUSER - 1);
	thread_unlock(curthread);

	while (!softc->shutdown) {
		/*
		 * We handle the queues in this order:
		 * - ISC
		 * - done queue (to free up resources, unblock other commands)
		 * - incoming queue
		 * - RtR queue
		 *
		 * If those queues are empty, we break out of the loop and
		 * go to sleep.
		 */
		mtx_lock(&thr->queue_lock);
		io = (union ctl_io *)STAILQ_FIRST(&thr->isc_queue);
		if (io != NULL) {
			STAILQ_REMOVE_HEAD(&thr->isc_queue, links);
			mtx_unlock(&thr->queue_lock);
			ctl_handle_isc(io);
			continue;
		}
		io = (union ctl_io *)STAILQ_FIRST(&thr->done_queue);
		if (io != NULL) {
			STAILQ_REMOVE_HEAD(&thr->done_queue, links);
			/* clear any blocked commands, call fe_done */
			mtx_unlock(&thr->queue_lock);
			ctl_process_done(io);
			continue;
		}
		io = (union ctl_io *)STAILQ_FIRST(&thr->incoming_queue);
		if (io != NULL) {
			STAILQ_REMOVE_HEAD(&thr->incoming_queue, links);
			mtx_unlock(&thr->queue_lock);
			if (io->io_hdr.io_type == CTL_IO_TASK)
				ctl_run_task(io);
			else
				ctl_scsiio_precheck(softc, &io->scsiio);
			continue;
		}
		io = (union ctl_io *)STAILQ_FIRST(&thr->rtr_queue);
		if (io != NULL) {
			STAILQ_REMOVE_HEAD(&thr->rtr_queue, links);
			mtx_unlock(&thr->queue_lock);
			retval = ctl_scsiio(&io->scsiio);
			if (retval != CTL_RETVAL_COMPLETE)
				CTL_DEBUG_PRINT(("ctl_scsiio failed\n"));
			continue;
		}

		/* Sleep until we have something to do. */
		mtx_sleep(thr, &thr->queue_lock, PDROP, "-", 0);
	}
	thr->thread = NULL;
	kthread_exit();
}