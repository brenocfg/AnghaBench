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
struct fwnode_handle {int dummy; } ;

/* Variables and functions */
 int acpi_device_is_present (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_acpi_device_node (struct fwnode_handle const*) ; 
 int /*<<< orphan*/  to_acpi_device_node (struct fwnode_handle const*) ; 

__attribute__((used)) static bool acpi_fwnode_device_is_available(const struct fwnode_handle *fwnode)
{
	if (!is_acpi_device_node(fwnode))
		return false;

	return acpi_device_is_present(to_acpi_device_node(fwnode));
}