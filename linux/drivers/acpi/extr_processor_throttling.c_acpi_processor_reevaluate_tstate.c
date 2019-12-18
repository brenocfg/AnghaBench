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
struct TYPE_4__ {int throttling; } ;
struct TYPE_3__ {scalar_t__ state; int /*<<< orphan*/  state_count; } ;
struct acpi_processor {TYPE_2__ flags; TYPE_1__ throttling; } ;

/* Variables and functions */
 int acpi_processor_get_throttling (struct acpi_processor*) ; 
 int acpi_processor_set_throttling (struct acpi_processor*,int /*<<< orphan*/ ,int) ; 

void acpi_processor_reevaluate_tstate(struct acpi_processor *pr,
					bool is_dead)
{
	int result = 0;

	if (is_dead) {
		/* When one CPU is offline, the T-state throttling
		 * will be invalidated.
		 */
		pr->flags.throttling = 0;
		return;
	}
	/* the following is to recheck whether the T-state is valid for
	 * the online CPU
	 */
	if (!pr->throttling.state_count) {
		/* If the number of T-state is invalid, it is
		 * invalidated.
		 */
		pr->flags.throttling = 0;
		return;
	}
	pr->flags.throttling = 1;

	/* Disable throttling (if enabled).  We'll let subsequent
	 * policy (e.g.thermal) decide to lower performance if it
	 * so chooses, but for now we'll crank up the speed.
	 */

	result = acpi_processor_get_throttling(pr);
	if (result)
		goto end;

	if (pr->throttling.state) {
		result = acpi_processor_set_throttling(pr, 0, false);
		if (result)
			goto end;
	}

end:
	if (result)
		pr->flags.throttling = 0;
}