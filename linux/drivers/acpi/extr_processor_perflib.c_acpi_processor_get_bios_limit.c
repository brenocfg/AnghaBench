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
struct acpi_processor {size_t performance_platform_limit; TYPE_2__* performance; } ;
struct TYPE_4__ {TYPE_1__* states; int /*<<< orphan*/  state_count; } ;
struct TYPE_3__ {int core_frequency; } ;

/* Variables and functions */
 int ENODEV ; 
 struct acpi_processor* per_cpu (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  processors ; 

int acpi_processor_get_bios_limit(int cpu, unsigned int *limit)
{
	struct acpi_processor *pr;

	pr = per_cpu(processors, cpu);
	if (!pr || !pr->performance || !pr->performance->state_count)
		return -ENODEV;
	*limit = pr->performance->states[pr->performance_platform_limit].
		core_frequency * 1000;
	return 0;
}