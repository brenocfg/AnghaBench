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
struct bufdomain {int /*<<< orphan*/  bd_running; } ;

/* Variables and functions */
 int /*<<< orphan*/  BD_RUN_LOCK (struct bufdomain*) ; 
 int /*<<< orphan*/  BD_RUN_UNLOCK (struct bufdomain*) ; 
 scalar_t__ atomic_fetchadd_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  atomic_store_int (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bufspace_daemon_wakeup(struct bufdomain *bd)
{

	/*
	 * avoid the lock if the daemon is running.
	 */
	if (atomic_fetchadd_int(&bd->bd_running, 1) == 0) {
		BD_RUN_LOCK(bd);
		atomic_store_int(&bd->bd_running, 1);
		wakeup(&bd->bd_running);
		BD_RUN_UNLOCK(bd);
	}
}