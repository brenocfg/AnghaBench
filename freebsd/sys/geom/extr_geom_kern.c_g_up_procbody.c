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

/* Variables and functions */
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  g_io_schedule_up (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_up_td ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_up_procbody(void *arg)
{

	thread_lock(g_up_td);
	sched_prio(g_up_td, PRIBIO);
	thread_unlock(g_up_td);
	for(;;) {
		g_io_schedule_up(g_up_td);
	}
}