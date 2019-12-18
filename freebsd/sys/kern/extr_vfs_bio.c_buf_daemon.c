#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct bufdomain {int bd_numdirtybuffers; int bd_lodirtybuffers; } ;
struct TYPE_3__ {int td_pflags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIT_EMPTY (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BUF_DOMAINS ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  PRI_USER ; 
 int /*<<< orphan*/  PVM ; 
 scalar_t__ SHUTDOWN_PRI_LAST ; 
 int TDP_BUFNEED ; 
 int TDP_NORUNNINGBUF ; 
 scalar_t__ bd_request ; 
 int bd_speedupreq ; 
 int /*<<< orphan*/  bdirtywakeup () ; 
 int /*<<< orphan*/  bdlock ; 
 int /*<<< orphan*/  bdlodirty ; 
 struct bufdomain* bdomain ; 
 int buf_domains ; 
 scalar_t__ buf_flush (int /*<<< orphan*/ *,struct bufdomain*,int) ; 
 scalar_t__ bufspace_daemon ; 
 int /*<<< orphan*/  curproc ; 
 TYPE_1__* curthread ; 
 int hz ; 
 int /*<<< orphan*/  kern_yield (int /*<<< orphan*/ ) ; 
 int kthread_add (void (*) (void*),struct bufdomain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kthread_shutdown ; 
 int /*<<< orphan*/  kthread_suspend_check () ; 
 scalar_t__ lorunningspace ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,int) ; 
 scalar_t__ runningbufspace ; 
 int /*<<< orphan*/  runningwakeup () ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 

__attribute__((used)) static void
buf_daemon()
{
	struct bufdomain *bd;
	int speedupreq;
	int lodirty;
	int i;

	/*
	 * This process needs to be suspended prior to shutdown sync.
	 */
	EVENTHANDLER_REGISTER(shutdown_pre_sync, kthread_shutdown, curthread,
	    SHUTDOWN_PRI_LAST + 100);

	/*
	 * Start the buf clean daemons as children threads.
	 */
	for (i = 0 ; i < buf_domains; i++) {
		int error;

		error = kthread_add((void (*)(void *))bufspace_daemon,
		    &bdomain[i], curproc, NULL, 0, 0, "bufspacedaemon-%d", i);
		if (error)
			panic("error %d spawning bufspace daemon", error);
	}

	/*
	 * This process is allowed to take the buffer cache to the limit
	 */
	curthread->td_pflags |= TDP_NORUNNINGBUF | TDP_BUFNEED;
	mtx_lock(&bdlock);
	for (;;) {
		bd_request = 0;
		mtx_unlock(&bdlock);

		kthread_suspend_check();

		/*
		 * Save speedupreq for this pass and reset to capture new
		 * requests.
		 */
		speedupreq = bd_speedupreq;
		bd_speedupreq = 0;

		/*
		 * Flush each domain sequentially according to its level and
		 * the speedup request.
		 */
		for (i = 0; i < buf_domains; i++) {
			bd = &bdomain[i];
			if (speedupreq)
				lodirty = bd->bd_numdirtybuffers / 2;
			else
				lodirty = bd->bd_lodirtybuffers;
			while (bd->bd_numdirtybuffers > lodirty) {
				if (buf_flush(NULL, bd,
				    bd->bd_numdirtybuffers - lodirty) == 0)
					break;
				kern_yield(PRI_USER);
			}
		}

		/*
		 * Only clear bd_request if we have reached our low water
		 * mark.  The buf_daemon normally waits 1 second and
		 * then incrementally flushes any dirty buffers that have
		 * built up, within reason.
		 *
		 * If we were unable to hit our low water mark and couldn't
		 * find any flushable buffers, we sleep for a short period
		 * to avoid endless loops on unlockable buffers.
		 */
		mtx_lock(&bdlock);
		if (!BIT_EMPTY(BUF_DOMAINS, &bdlodirty)) {
			/*
			 * We reached our low water mark, reset the
			 * request and sleep until we are needed again.
			 * The sleep is just so the suspend code works.
			 */
			bd_request = 0;
			/*
			 * Do an extra wakeup in case dirty threshold
			 * changed via sysctl and the explicit transition
			 * out of shortfall was missed.
			 */
			bdirtywakeup();
			if (runningbufspace <= lorunningspace)
				runningwakeup();
			msleep(&bd_request, &bdlock, PVM, "psleep", hz);
		} else {
			/*
			 * We couldn't find any flushable dirty buffers but
			 * still have too many dirty buffers, we
			 * have to sleep and try again.  (rare)
			 */
			msleep(&bd_request, &bdlock, PVM, "qsleep", hz / 10);
		}
	}
}