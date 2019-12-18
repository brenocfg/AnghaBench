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
typedef  int /*<<< orphan*/  evt ;

/* Variables and functions */
 int MAX_MC_EVT ; 
 int /*<<< orphan*/  MCE_EVENT_RELEASE ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_inc_return (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mce_event (struct machine_check_event*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_work_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mce_event_process_work ; 
 int /*<<< orphan*/ * mce_event_queue ; 
 int /*<<< orphan*/  mce_queue_count ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,struct machine_check_event*,int) ; 
 int /*<<< orphan*/  this_cpu_ptr (int /*<<< orphan*/ *) ; 

void machine_check_queue_event(void)
{
	int index;
	struct machine_check_event evt;

	if (!get_mce_event(&evt, MCE_EVENT_RELEASE))
		return;

	index = __this_cpu_inc_return(mce_queue_count) - 1;
	/* If queue is full, just return for now. */
	if (index >= MAX_MC_EVT) {
		__this_cpu_dec(mce_queue_count);
		return;
	}
	memcpy(this_cpu_ptr(&mce_event_queue[index]), &evt, sizeof(evt));

	/* Queue irq work to process this event later. */
	irq_work_queue(&mce_event_process_work);
}