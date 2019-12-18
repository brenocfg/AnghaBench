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
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 char* AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 char* acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 

__attribute__((used)) static void
vid_set_switch_policy(ACPI_HANDLE handle, UINT32 policy)
{
	ACPI_STATUS status;

	status = acpi_SetInteger(handle, "_DOS", policy);
	if (ACPI_FAILURE(status))
		printf("can't evaluate %s._DOS - %s\n",
		       acpi_name(handle), AcpiFormatException(status));
}