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
typedef  scalar_t__ u64 ;
struct TYPE_4__ {int state; } ;
struct TYPE_3__ {int /*<<< orphan*/  throttling; } ;
struct acpi_processor {TYPE_2__ throttling; TYPE_1__ flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int EINVAL ; 
 int ENODEV ; 
 int __acpi_processor_set_throttling (struct acpi_processor*,int,int,int) ; 
 int acpi_get_throttling_state (struct acpi_processor*,scalar_t__) ; 
 int acpi_read_throttling_status (struct acpi_processor*,scalar_t__*) ; 

__attribute__((used)) static int acpi_processor_get_throttling_ptc(struct acpi_processor *pr)
{
	int state = 0;
	int ret;
	u64 value;

	if (!pr)
		return -EINVAL;

	if (!pr->flags.throttling)
		return -ENODEV;

	pr->throttling.state = 0;

	value = 0;
	ret = acpi_read_throttling_status(pr, &value);
	if (ret >= 0) {
		state = acpi_get_throttling_state(pr, value);
		if (state == -1) {
			ACPI_DEBUG_PRINT((ACPI_DB_INFO,
				"Invalid throttling state, reset\n"));
			state = 0;
			ret = __acpi_processor_set_throttling(pr, state, true,
							      true);
			if (ret)
				return ret;
		}
		pr->throttling.state = state;
	}

	return 0;
}