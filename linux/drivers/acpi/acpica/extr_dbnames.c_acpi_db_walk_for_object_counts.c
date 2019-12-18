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
typedef  int /*<<< orphan*/  u32 ;
struct acpi_object_info {int /*<<< orphan*/ * types; } ;
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {size_t type; TYPE_1__ name; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 size_t ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static acpi_status
acpi_db_walk_for_object_counts(acpi_handle obj_handle,
			       u32 nesting_level,
			       void *context, void **return_value)
{
	struct acpi_object_info *info = (struct acpi_object_info *)context;
	struct acpi_namespace_node *node =
	    (struct acpi_namespace_node *)obj_handle;

	if (node->type > ACPI_TYPE_NS_NODE_MAX) {
		acpi_os_printf("[%4.4s]: Unknown object type %X\n",
			       node->name.ascii, node->type);
	} else {
		info->types[node->type]++;
	}

	return (AE_OK);
}