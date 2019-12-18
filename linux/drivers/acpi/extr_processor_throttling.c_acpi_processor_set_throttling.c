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
struct acpi_processor {int dummy; } ;

/* Variables and functions */
 int __acpi_processor_set_throttling (struct acpi_processor*,int,int,int) ; 

int acpi_processor_set_throttling(struct acpi_processor *pr, int state,
				  bool force)
{
	return __acpi_processor_set_throttling(pr, state, force, false);
}