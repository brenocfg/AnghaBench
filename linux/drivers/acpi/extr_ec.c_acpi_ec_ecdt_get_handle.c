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
struct acpi_table_header {int dummy; } ;
struct acpi_table_ecdt {int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SIG_ECDT ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_get_table (int /*<<< orphan*/ ,int,struct acpi_table_header**) ; 

__attribute__((used)) static bool acpi_ec_ecdt_get_handle(acpi_handle *phandle)
{
	struct acpi_table_ecdt *ecdt_ptr;
	acpi_status status;
	acpi_handle handle;

	status = acpi_get_table(ACPI_SIG_ECDT, 1,
				(struct acpi_table_header **)&ecdt_ptr);
	if (ACPI_FAILURE(status))
		return false;

	status = acpi_get_handle(NULL, ecdt_ptr->id, &handle);
	if (ACPI_FAILURE(status))
		return false;

	*phandle = handle;
	return true;
}