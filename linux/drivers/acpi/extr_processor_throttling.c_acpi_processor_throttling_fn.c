#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct acpi_processor_throttling_arg {int /*<<< orphan*/  force; int /*<<< orphan*/  target_state; struct acpi_processor* pr; } ;
struct TYPE_2__ {long (* acpi_processor_set_throttling ) (struct acpi_processor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct acpi_processor {TYPE_1__ throttling; } ;

/* Variables and functions */
 long stub1 (struct acpi_processor*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static long acpi_processor_throttling_fn(void *data)
{
	struct acpi_processor_throttling_arg *arg = data;
	struct acpi_processor *pr = arg->pr;

	return pr->throttling.acpi_processor_set_throttling(pr,
			arg->target_state, arg->force);
}