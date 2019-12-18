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
struct TYPE_2__ {int /*<<< orphan*/  count; } ;
union acpi_object {TYPE_1__ package; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  acpi_db_read_from_object (struct acpi_namespace_node*,int /*<<< orphan*/ ,union acpi_object**) ; 
 int /*<<< orphan*/  acpi_os_free (union acpi_object*) ; 
 int /*<<< orphan*/  acpi_os_printf (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status acpi_db_test_package_type(struct acpi_namespace_node *node)
{
	union acpi_object *temp1 = NULL;
	acpi_status status;

	/* Read the original value */

	status = acpi_db_read_from_object(node, ACPI_TYPE_PACKAGE, &temp1);
	if (ACPI_FAILURE(status)) {
		return (status);
	}

	acpi_os_printf(" %.2X Elements", temp1->package.count);
	acpi_os_free(temp1);
	return (status);
}