#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {size_t Length; char* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SINGLE_NAME ; 
 int /*<<< orphan*/  AcpiGetName (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static ACPI_STATUS
acpi_short_name(ACPI_HANDLE handle, char *buffer, size_t buflen)
{
	ACPI_BUFFER buf;

	buf.Length = buflen;
	buf.Pointer = buffer;
	return (AcpiGetName(handle, ACPI_SINGLE_NAME, &buf));
}