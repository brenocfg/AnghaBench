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
 int /*<<< orphan*/  g_down_td ; 
 int /*<<< orphan*/  g_io_schedule_down (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_prio (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_down_procbody(void *arg)
{

	thread_lock(g_down_td);
	sched_prio(g_down_td, PRIBIO);
	thread_unlock(g_down_td);
	for(;;) {
		g_io_schedule_down(g_down_td);
	}
}