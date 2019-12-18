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
struct acpi_namespace_node {int flags; int type; } ;

/* Variables and functions */
#define  ACPI_TYPE_DEVICE 129 
#define  ACPI_TYPE_THERMAL 128 
 int ANOBJ_METHOD_ARG ; 
 int ANOBJ_METHOD_LOCAL ; 
 int /*<<< orphan*/  acpi_db_decode_internal_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ns_get_attached_object (struct acpi_namespace_node*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,...) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (struct acpi_namespace_node*) ; 

__attribute__((used)) static void acpi_db_decode_node(struct acpi_namespace_node *node)
{

	acpi_os_printf("<Node>          Name %4.4s",
		       acpi_ut_get_node_name(node));

	if (node->flags & ANOBJ_METHOD_ARG) {
		acpi_os_printf(" [Method Arg]");
	}
	if (node->flags & ANOBJ_METHOD_LOCAL) {
		acpi_os_printf(" [Method Local]");
	}

	switch (node->type) {

		/* These types have no attached object */

	case ACPI_TYPE_DEVICE:

		acpi_os_printf(" Device");
		break;

	case ACPI_TYPE_THERMAL:

		acpi_os_printf(" Thermal Zone");
		break;

	default:

		acpi_db_decode_internal_object(acpi_ns_get_attached_object
					       (node));
		break;
	}
}