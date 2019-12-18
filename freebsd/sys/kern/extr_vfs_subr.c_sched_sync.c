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
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_pflags; } ;
struct synclist {int dummy; } ;
struct bufobj {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ LIST_EMPTY (struct synclist*) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (struct synclist*,struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct bufobj*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PPAUSE ; 
 int /*<<< orphan*/  SHUTDOWN_PRI_LAST ; 
 scalar_t__ SYNCER_FINAL_DELAY ; 
 scalar_t__ SYNCER_RUNNING ; 
 int SYNCER_SHUTDOWN_SPEEDUP ; 
 scalar_t__ SYNCER_SHUTTING_DOWN ; 
 int /*<<< orphan*/  TDP_NORUNNINGBUF ; 
 int /*<<< orphan*/  WD_LASTVAL ; 
 int /*<<< orphan*/  bo_synclist ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  cv_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ first_printf ; 
 int hz ; 
 int /*<<< orphan*/  kproc_suspend_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ rushjob ; 
 int /*<<< orphan*/  sched_prio (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 
 int /*<<< orphan*/  sync_mtx ; 
 int sync_vnode (struct synclist*,struct bufobj**,struct thread*) ; 
 scalar_t__ sync_vnode_count ; 
 int /*<<< orphan*/  sync_wakeup ; 
 size_t syncer_delayno ; 
 size_t syncer_maxdelay ; 
 int /*<<< orphan*/  syncer_shutdown ; 
 scalar_t__ syncer_state ; 
 struct synclist* syncer_workitem_pending ; 
 scalar_t__ syncer_worklist_len ; 
 int /*<<< orphan*/  thread_lock (struct thread*) ; 
 int /*<<< orphan*/  thread_unlock (struct thread*) ; 
 long time_uptime ; 
 int /*<<< orphan*/  wdog_kern_pat (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
sched_sync(void)
{
	struct synclist *next, *slp;
	struct bufobj *bo;
	long starttime;
	struct thread *td = curthread;
	int last_work_seen;
	int net_worklist_len;
	int syncer_final_iter;
	int error;

	last_work_seen = 0;
	syncer_final_iter = 0;
	syncer_state = SYNCER_RUNNING;
	starttime = time_uptime;
	td->td_pflags |= TDP_NORUNNINGBUF;

	EVENTHANDLER_REGISTER(shutdown_pre_sync, syncer_shutdown, td->td_proc,
	    SHUTDOWN_PRI_LAST);

	mtx_lock(&sync_mtx);
	for (;;) {
		if (syncer_state == SYNCER_FINAL_DELAY &&
		    syncer_final_iter == 0) {
			mtx_unlock(&sync_mtx);
			kproc_suspend_check(td->td_proc);
			mtx_lock(&sync_mtx);
		}
		net_worklist_len = syncer_worklist_len - sync_vnode_count;
		if (syncer_state != SYNCER_RUNNING &&
		    starttime != time_uptime) {
			if (first_printf) {
				printf("\nSyncing disks, vnodes remaining... ");
				first_printf = 0;
			}
			printf("%d ", net_worklist_len);
		}
		starttime = time_uptime;

		/*
		 * Push files whose dirty time has expired.  Be careful
		 * of interrupt race on slp queue.
		 *
		 * Skip over empty worklist slots when shutting down.
		 */
		do {
			slp = &syncer_workitem_pending[syncer_delayno];
			syncer_delayno += 1;
			if (syncer_delayno == syncer_maxdelay)
				syncer_delayno = 0;
			next = &syncer_workitem_pending[syncer_delayno];
			/*
			 * If the worklist has wrapped since the
			 * it was emptied of all but syncer vnodes,
			 * switch to the FINAL_DELAY state and run
			 * for one more second.
			 */
			if (syncer_state == SYNCER_SHUTTING_DOWN &&
			    net_worklist_len == 0 &&
			    last_work_seen == syncer_delayno) {
				syncer_state = SYNCER_FINAL_DELAY;
				syncer_final_iter = SYNCER_SHUTDOWN_SPEEDUP;
			}
		} while (syncer_state != SYNCER_RUNNING && LIST_EMPTY(slp) &&
		    syncer_worklist_len > 0);

		/*
		 * Keep track of the last time there was anything
		 * on the worklist other than syncer vnodes.
		 * Return to the SHUTTING_DOWN state if any
		 * new work appears.
		 */
		if (net_worklist_len > 0 || syncer_state == SYNCER_RUNNING)
			last_work_seen = syncer_delayno;
		if (net_worklist_len > 0 && syncer_state == SYNCER_FINAL_DELAY)
			syncer_state = SYNCER_SHUTTING_DOWN;
		while (!LIST_EMPTY(slp)) {
			error = sync_vnode(slp, &bo, td);
			if (error == 1) {
				LIST_REMOVE(bo, bo_synclist);
				LIST_INSERT_HEAD(next, bo, bo_synclist);
				continue;
			}

			if (first_printf == 0) {
				/*
				 * Drop the sync mutex, because some watchdog
				 * drivers need to sleep while patting
				 */
				mtx_unlock(&sync_mtx);
				wdog_kern_pat(WD_LASTVAL);
				mtx_lock(&sync_mtx);
			}

		}
		if (syncer_state == SYNCER_FINAL_DELAY && syncer_final_iter > 0)
			syncer_final_iter--;
		/*
		 * The variable rushjob allows the kernel to speed up the
		 * processing of the filesystem syncer process. A rushjob
		 * value of N tells the filesystem syncer to process the next
		 * N seconds worth of work on its queue ASAP. Currently rushjob
		 * is used by the soft update code to speed up the filesystem
		 * syncer process when the incore state is getting so far
		 * ahead of the disk that the kernel memory pool is being
		 * threatened with exhaustion.
		 */
		if (rushjob > 0) {
			rushjob -= 1;
			continue;
		}
		/*
		 * Just sleep for a short period of time between
		 * iterations when shutting down to allow some I/O
		 * to happen.
		 *
		 * If it has taken us less than a second to process the
		 * current work, then wait. Otherwise start right over
		 * again. We can still lose time if any single round
		 * takes more than two seconds, but it does not really
		 * matter as we are just trying to generally pace the
		 * filesystem activity.
		 */
		if (syncer_state != SYNCER_RUNNING ||
		    time_uptime == starttime) {
			thread_lock(td);
			sched_prio(td, PPAUSE);
			thread_unlock(td);
		}
		if (syncer_state != SYNCER_RUNNING)
			cv_timedwait(&sync_wakeup, &sync_mtx,
			    hz / SYNCER_SHUTDOWN_SPEEDUP);
		else if (time_uptime == starttime)
			cv_timedwait(&sync_wakeup, &sync_mtx, hz);
	}
}