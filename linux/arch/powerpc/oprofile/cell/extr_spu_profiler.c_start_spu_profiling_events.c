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
 int /*<<< orphan*/  DEFAULT_TIMER_EXPIRE ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int spu_prof_running ; 
 int /*<<< orphan*/  spu_work ; 

void start_spu_profiling_events(void)
{
	spu_prof_running = 1;
	schedule_delayed_work(&spu_work, DEFAULT_TIMER_EXPIRE);

	return;
}