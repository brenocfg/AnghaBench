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
typedef  int /*<<< orphan*/  pm_message_t ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  dpm_resume_early (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dpm_show_time (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int dpm_suspend_late (int /*<<< orphan*/ ) ; 
 int dpm_suspend_noirq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  resume_event (int /*<<< orphan*/ ) ; 

int dpm_suspend_end(pm_message_t state)
{
	ktime_t starttime = ktime_get();
	int error;

	error = dpm_suspend_late(state);
	if (error)
		goto out;

	error = dpm_suspend_noirq(state);
	if (error)
		dpm_resume_early(resume_event(state));

out:
	dpm_show_time(starttime, state, error, "end");
	return error;
}