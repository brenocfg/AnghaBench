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
struct machine_check_event {int dummy; } ;

/* Variables and functions */
 int MAX_MC_EVT ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_ue_count ; 
 int /*<<< orphan*/  mce_ue_event_irq_work ; 
 int /*<<< orphan*/ * mce_ue_event_queue ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct machine_check_event*,int) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void machine_check_ue_event(struct machine_check_event *evt)
{
	int index;

	index = __this_cpu_inc_return(mce_ue_count) - 1;
	/* If queue is full, just return for now. */
	if (index >= MAX_MC_EVT) {
		__this_cpu_dec(mce_ue_count);
		return;
	}
	memcpy(this_cpu_ptr(&mce_ue_event_queue[index]), evt, sizeof(*evt));

	/* Queue work to process this event later. */
	irq_work_queue(&mce_ue_event_irq_work);
}