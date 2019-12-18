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
struct fwnode_handle {int dummy; } ;
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 scalar_t__ fwnode_property_present (struct fwnode_handle*,char const*) ; 
 int /*<<< orphan*/  is_acpi_data_node (struct fwnode_handle*) ; 
 unsigned int strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,unsigned int) ; 
 TYPE_1__* to_acpi_data_node (struct fwnode_handle*) ; 

__attribute__((used)) static bool is_acpi_graph_node(struct fwnode_handle *fwnode,
			       const char *str)
{
	unsigned int len = strlen(str);
	const char *name;

	if (!len || !is_acpi_data_node(fwnode))
		return false;

	name = to_acpi_data_node(fwnode)->name;

	return (fwnode_property_present(fwnode, "reg") &&
		!strncmp(name, str, len) && name[len] == '@') ||
		fwnode_property_present(fwnode, str);
}