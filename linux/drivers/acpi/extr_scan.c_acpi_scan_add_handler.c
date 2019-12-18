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
struct acpi_scan_handler {int /*<<< orphan*/  list_node; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  acpi_scan_handlers_list ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int acpi_scan_add_handler(struct acpi_scan_handler *handler)
{
	if (!handler)
		return -EINVAL;

	list_add_tail(&handler->list_node, &acpi_scan_handlers_list);
	return 0;
}