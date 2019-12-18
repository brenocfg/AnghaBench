#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ignore_event; } ;
struct TYPE_4__ {TYPE_1__ ue_error; } ;
struct machine_check_event {scalar_t__ error_type; TYPE_2__ u; } ;
struct irq_work {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOCKDEP_NOW_UNRELIABLE ; 
 scalar_t__ MCE_ERROR_TYPE_UE ; 
 int /*<<< orphan*/  TAINT_MACHINE_CHECK ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_taint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  machine_check_print_event_info (struct machine_check_event*,int,int) ; 
 int /*<<< orphan*/ * mce_event_queue ; 
 int /*<<< orphan*/  mce_queue_count ; 
 struct machine_check_event* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void machine_check_process_queued_event(struct irq_work *work)
{
	int index;
	struct machine_check_event *evt;

	add_taint(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

	/*
	 * For now just print it to console.
	 * TODO: log this error event to FSP or nvram.
	 */
	while (__this_cpu_read(mce_queue_count) > 0) {
		index = __this_cpu_read(mce_queue_count) - 1;
		evt = this_cpu_ptr(&mce_event_queue[index]);

		if (evt->error_type == MCE_ERROR_TYPE_UE &&
		    evt->u.ue_error.ignore_event) {
			__this_cpu_dec(mce_queue_count);
			continue;
		}
		machine_check_print_event_info(evt, false, false);
		__this_cpu_dec(mce_queue_count);
	}
}