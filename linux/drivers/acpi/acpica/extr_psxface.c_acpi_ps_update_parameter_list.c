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
typedef  size_t u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct acpi_evaluate_info {scalar_t__* parameters; } ;

/* Variables and functions */
 int /*<<< orphan*/  acpi_ut_update_object_reference (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
acpi_ps_update_parameter_list(struct acpi_evaluate_info *info, u16 action)
{
	u32 i;

	if (info->parameters) {

		/* Update reference count for each parameter */

		for (i = 0; info->parameters[i]; i++) {

			/* Ignore errors, just do them all */

			(void)acpi_ut_update_object_reference(info->
							      parameters[i],
							      action);
		}
	}
}