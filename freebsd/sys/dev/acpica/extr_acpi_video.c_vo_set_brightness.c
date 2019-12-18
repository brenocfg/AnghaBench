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
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 char* AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_SetInteger (int /*<<< orphan*/ ,char*,int) ; 
 char* acpi_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*) ; 
 int /*<<< orphan*/  video_output ; 

__attribute__((used)) static void
vo_set_brightness(ACPI_HANDLE handle, int level)
{
	ACPI_STATUS status;

	ACPI_SERIAL_ASSERT(video_output);
	status = acpi_SetInteger(handle, "_BCM", level);
	if (ACPI_FAILURE(status))
		printf("can't evaluate %s._BCM - %s\n",
		       acpi_name(handle), AcpiFormatException(status));
}