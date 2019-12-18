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
struct TYPE_3__ {int targ_port; int initid; } ;
struct TYPE_4__ {TYPE_1__ nexus; } ;
union ctl_io {TYPE_2__ io_hdr; } ;
typedef  size_t u_int ;
struct ctl_thread {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  incoming_queue; } ;
struct ctl_softc {struct ctl_thread* threads; } ;

/* Variables and functions */
 struct ctl_softc* CTL_SOFTC (union ctl_io*) ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  links ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct ctl_thread*) ; 
 int worker_threads ; 

__attribute__((used)) static void
ctl_enqueue_incoming(union ctl_io *io)
{
	struct ctl_softc *softc = CTL_SOFTC(io);
	struct ctl_thread *thr;
	u_int idx;

	idx = (io->io_hdr.nexus.targ_port * 127 +
	       io->io_hdr.nexus.initid) % worker_threads;
	thr = &softc->threads[idx];
	mtx_lock(&thr->queue_lock);
	STAILQ_INSERT_TAIL(&thr->incoming_queue, &io->io_hdr, links);
	mtx_unlock(&thr->queue_lock);
	wakeup(thr);
}