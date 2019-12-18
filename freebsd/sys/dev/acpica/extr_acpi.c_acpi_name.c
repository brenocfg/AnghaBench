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
typedef  int /*<<< orphan*/  data ;
struct TYPE_3__ {int Length; char* Pointer; } ;
typedef  scalar_t__ ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetName (scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 

char *
acpi_name(ACPI_HANDLE handle)
{
    ACPI_BUFFER buf;
    static char data[256];

    buf.Length = sizeof(data);
    buf.Pointer = data;

    if (handle && ACPI_SUCCESS(AcpiGetName(handle, ACPI_FULL_PATHNAME, &buf)))
	return (data);
    return ("(unknown)");
}