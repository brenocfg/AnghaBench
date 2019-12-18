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
struct acpi_device {int dummy; } ;

/* Variables and functions */
 int aml_nfw_add_global_handler () ; 

__attribute__((used)) static int aml_nfw_add(struct acpi_device *device)
{
	/*
	 * We would normally allocate a new context structure and install
	 * the address space handler for the specific device we found.
	 * But the HP-UX implementation shares a single global context
	 * and always puts the handler at the root, so we'll do the same.
	 */
	return aml_nfw_add_global_handler();
}