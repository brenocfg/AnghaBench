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
struct work_struct {int dummy; } ;
struct TYPE_4__ {unsigned long physical_address; scalar_t__ physical_address_provided; scalar_t__ ignore_event; } ;
struct TYPE_3__ {TYPE_2__ ue_error; } ;
struct machine_check_event {scalar_t__ error_type; TYPE_1__ u; } ;

/* Variables and functions */
 scalar_t__ MCE_ERROR_TYPE_UE ; 
 unsigned long PAGE_SHIFT ; 
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mce_ue_count ; 
 int /*<<< orphan*/ * mce_ue_event_queue ; 
 int /*<<< orphan*/  memory_failure (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 struct machine_check_event* this_cpu_ptr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void machine_process_ue_event(struct work_struct *work)
{
	int index;
	struct machine_check_event *evt;

	while (__this_cpu_read(mce_ue_count) > 0) {
		index = __this_cpu_read(mce_ue_count) - 1;
		evt = this_cpu_ptr(&mce_ue_event_queue[index]);
#ifdef CONFIG_MEMORY_FAILURE
		/*
		 * This should probably queued elsewhere, but
		 * oh! well
		 *
		 * Don't report this machine check because the caller has a
		 * asked us to ignore the event, it has a fixup handler which
		 * will do the appropriate error handling and reporting.
		 */
		if (evt->error_type == MCE_ERROR_TYPE_UE) {
			if (evt->u.ue_error.ignore_event) {
				__this_cpu_dec(mce_ue_count);
				continue;
			}

			if (evt->u.ue_error.physical_address_provided) {
				unsigned long pfn;

				pfn = evt->u.ue_error.physical_address >>
					PAGE_SHIFT;
				memory_failure(pfn, 0);
			} else
				pr_warn("Failed to identify bad address from "
					"where the uncorrectable error (UE) "
					"was generated\n");
		}
#endif
		__this_cpu_dec(mce_ue_count);
	}
}