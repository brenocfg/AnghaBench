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
struct TYPE_2__ {int /*<<< orphan*/  ascii; } ;
struct acpi_namespace_node {scalar_t__ type; TYPE_1__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_CONSOLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_DB_REDIRECTABLE_OUTPUT ; 
 int /*<<< orphan*/  ACPI_LV_RESOURCES ; 
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 scalar_t__ ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 struct acpi_namespace_node* acpi_db_convert_to_node (char*) ; 
 int /*<<< orphan*/  acpi_db_device_resources (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_db_set_output_destination (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_dbg_level ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (scalar_t__) ; 
 int /*<<< orphan*/  acpi_walk_namespace (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (struct acpi_namespace_node*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *),int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

void acpi_db_display_resources(char *object_arg)
{
	struct acpi_namespace_node *node;

	acpi_db_set_output_destination(ACPI_DB_REDIRECTABLE_OUTPUT);
	acpi_dbg_level |= ACPI_LV_RESOURCES;

	/* Asterisk means "display resources for all devices" */

	if (!object_arg || (!strcmp(object_arg, "*"))) {
		(void)acpi_walk_namespace(ACPI_TYPE_DEVICE, ACPI_ROOT_OBJECT,
					  ACPI_UINT32_MAX,
					  acpi_db_device_resources, NULL, NULL,
					  NULL);
	} else {
		/* Convert string to object pointer */

		node = acpi_db_convert_to_node(object_arg);
		if (node) {
			if (node->type != ACPI_TYPE_DEVICE) {
				acpi_os_printf
				    ("%4.4s: Name is not a device object (%s)\n",
				     node->name.ascii,
				     acpi_ut_get_type_name(node->type));
			} else {
				(void)acpi_db_device_resources(node, 0, NULL,
							       NULL);
			}
		}
	}

	acpi_db_set_output_destination(ACPI_DB_CONSOLE_OUTPUT);
}