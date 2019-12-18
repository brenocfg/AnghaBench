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
typedef  int time_t ;
struct remote_lock {int start_time; int timeout; char* url; struct remote_lock* next; int /*<<< orphan*/  refreshing; } ;
struct TYPE_2__ {struct remote_lock* locks; } ;

/* Variables and functions */
 int LOCK_REFRESH ; 
 int aborted ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  refresh_lock (struct remote_lock*) ; 
 TYPE_1__* repo ; 
 int /*<<< orphan*/  stderr ; 
 int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_locks(void)
{
	struct remote_lock *lock = repo->locks;
	time_t current_time = time(NULL);
	int time_remaining;

	while (lock) {
		time_remaining = lock->start_time + lock->timeout -
			current_time;
		if (!lock->refreshing && time_remaining < LOCK_REFRESH) {
			if (!refresh_lock(lock)) {
				fprintf(stderr,
					"Unable to refresh lock for %s\n",
					lock->url);
				aborted = 1;
				return;
			}
		}
		lock = lock->next;
	}
}