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
struct bufdomain {scalar_t__ bd_bufspace; scalar_t__ bd_bufspacethresh; scalar_t__ bd_freebuffers; scalar_t__ bd_lofreebuffers; int /*<<< orphan*/  bd_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_RUN_LOCK (struct bufdomain*) ; 
 int /*<<< orphan*/  BD_RUN_LOCKPTR (struct bufdomain*) ; 
 int /*<<< orphan*/  BD_RUN_UNLOCK (struct bufdomain*) ; 
 int PDROP ; 
 int PRIBIO ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bufspace_daemon_wait(struct bufdomain *bd)
{
	/*
	 * Re-check our limits and sleep.  bd_running must be
	 * cleared prior to checking the limits to avoid missed
	 * wakeups.  The waker will adjust one of bufspace or
	 * freebuffers prior to checking bd_running.
	 */
	BD_RUN_LOCK(bd);
	atomic_store_int(&bd->bd_running, 0);
	if (bd->bd_bufspace < bd->bd_bufspacethresh &&
	    bd->bd_freebuffers > bd->bd_lofreebuffers) {
		msleep(&bd->bd_running, BD_RUN_LOCKPTR(bd), PRIBIO|PDROP,
		    "-", hz);
	} else {
		/* Avoid spurious wakeups while running. */
		atomic_store_int(&bd->bd_running, 1);
		BD_RUN_UNLOCK(bd);
	}
}