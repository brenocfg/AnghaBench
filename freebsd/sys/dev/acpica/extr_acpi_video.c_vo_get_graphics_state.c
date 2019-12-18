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
typedef  scalar_t__ UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 char* AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 char* acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static UINT32
vo_get_graphics_state(ACPI_HANDLE handle)
{
	UINT32 dgs;
	ACPI_STATUS status;

	dgs = 0;
	status = acpi_GetInteger(handle, "_DGS", &dgs);
	if (ACPI_FAILURE(status))
		printf("can't evaluate %s._DGS - %s\n",
		       acpi_name(handle), AcpiFormatException(status));

	return (dgs);
}