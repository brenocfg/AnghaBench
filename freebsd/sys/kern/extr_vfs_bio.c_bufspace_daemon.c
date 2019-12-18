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
struct bufdomain {scalar_t__ bd_bufspace; scalar_t__ bd_lobufspace; scalar_t__ bd_freebuffers; scalar_t__ bd_hifreebuffers; scalar_t__ bd_wanted; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_LOCK (struct bufdomain*) ; 
 int /*<<< orphan*/  BD_LOCKPTR (struct bufdomain*) ; 
 int /*<<< orphan*/  BD_UNLOCK (struct bufdomain*) ; 
 int /*<<< orphan*/  EVENTHANDLER_REGISTER (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int PDROP ; 
 int PRIBIO ; 
 scalar_t__ SHUTDOWN_PRI_LAST ; 
 scalar_t__ bd_flushall (struct bufdomain*) ; 
 int /*<<< orphan*/  bd_speedup () ; 
 scalar_t__ buf_recycle (struct bufdomain*,int) ; 
 int /*<<< orphan*/  bufspace_daemon_wait (struct bufdomain*) ; 
 int /*<<< orphan*/  curthread ; 
 int hz ; 
 int /*<<< orphan*/  kthread_shutdown ; 
 int /*<<< orphan*/  kthread_suspend_check () ; 
 int /*<<< orphan*/  maybe_yield () ; 
 int /*<<< orphan*/  msleep (scalar_t__*,int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  shutdown_pre_sync ; 

__attribute__((used)) static void
bufspace_daemon(void *arg)
{
	struct bufdomain *bd;

	EVENTHANDLER_REGISTER(shutdown_pre_sync, kthread_shutdown, curthread,
	    SHUTDOWN_PRI_LAST + 100);

	bd = arg;
	for (;;) {
		kthread_suspend_check();

		/*
		 * Free buffers from the clean queue until we meet our
		 * targets.
		 *
		 * Theory of operation:  The buffer cache is most efficient
		 * when some free buffer headers and space are always
		 * available to getnewbuf().  This daemon attempts to prevent
		 * the excessive blocking and synchronization associated
		 * with shortfall.  It goes through three phases according
		 * demand:
		 *
		 * 1)	The daemon wakes up voluntarily once per-second
		 *	during idle periods when the counters are below
		 *	the wakeup thresholds (bufspacethresh, lofreebuffers).
		 *
		 * 2)	The daemon wakes up as we cross the thresholds
		 *	ahead of any potential blocking.  This may bounce
		 *	slightly according to the rate of consumption and
		 *	release.
		 *
		 * 3)	The daemon and consumers are starved for working
		 *	clean buffers.  This is the 'bufspace' sleep below
		 *	which will inefficiently trade bufs with bqrelse
		 *	until we return to condition 2.
		 */
		while (bd->bd_bufspace > bd->bd_lobufspace ||
		    bd->bd_freebuffers < bd->bd_hifreebuffers) {
			if (buf_recycle(bd, false) != 0) {
				if (bd_flushall(bd))
					continue;
				/*
				 * Speedup dirty if we've run out of clean
				 * buffers.  This is possible in particular
				 * because softdep may held many bufs locked
				 * pending writes to other bufs which are
				 * marked for delayed write, exhausting
				 * clean space until they are written.
				 */
				bd_speedup();
				BD_LOCK(bd);
				if (bd->bd_wanted) {
					msleep(&bd->bd_wanted, BD_LOCKPTR(bd),
					    PRIBIO|PDROP, "bufspace", hz/10);
				} else
					BD_UNLOCK(bd);
			}
			maybe_yield();
		}
		bufspace_daemon_wait(bd);
	}
}