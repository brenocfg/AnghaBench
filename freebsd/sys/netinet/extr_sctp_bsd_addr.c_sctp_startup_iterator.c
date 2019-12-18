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
struct TYPE_2__ {scalar_t__ thread_proc; int /*<<< orphan*/  iteratorhead; } ;

/* Variables and functions */
 int /*<<< orphan*/  RFPROC ; 
 int /*<<< orphan*/  SCTP_IPI_ITERATOR_WQ_INIT () ; 
 int /*<<< orphan*/  SCTP_ITERATOR_LOCK_INIT () ; 
 int /*<<< orphan*/  SCTP_KTHREAD_PAGES ; 
 int /*<<< orphan*/  SCTP_KTRHEAD_NAME ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kproc_create (int /*<<< orphan*/ ,void*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ sctp_it_ctl ; 
 int /*<<< orphan*/  sctp_iterator_thread ; 

void
sctp_startup_iterator(void)
{
	if (sctp_it_ctl.thread_proc) {
		/* You only get one */
		return;
	}
	/* Initialize global locks here, thus only once. */
	SCTP_ITERATOR_LOCK_INIT();
	SCTP_IPI_ITERATOR_WQ_INIT();
	TAILQ_INIT(&sctp_it_ctl.iteratorhead);
	kproc_create(sctp_iterator_thread,
	    (void *)NULL,
	    &sctp_it_ctl.thread_proc,
	    RFPROC,
	    SCTP_KTHREAD_PAGES,
	    SCTP_KTRHEAD_NAME);
}