#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  param ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_10__ {int Length; TYPE_2__* Pointer; } ;
struct TYPE_8__ {int /*<<< orphan*/  Value; } ;
struct TYPE_9__ {scalar_t__ Type; TYPE_1__ Integer; } ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_ROOT_OBJECT ; 
 scalar_t__ ACPI_SUCCESS (scalar_t__) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ AE_BUFFER_OVERFLOW ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_TYPE ; 
 scalar_t__ AcpiEvaluateObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_2__* AcpiOsAllocate (int) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_2__*) ; 
 scalar_t__ acpi_ConvertBufferToInteger (TYPE_3__*,int /*<<< orphan*/ *) ; 

ACPI_STATUS
acpi_GetInteger(ACPI_HANDLE handle, char *path, UINT32 *number)
{
    ACPI_STATUS	status;
    ACPI_BUFFER	buf;
    ACPI_OBJECT	param;

    if (handle == NULL)
	handle = ACPI_ROOT_OBJECT;

    /*
     * Assume that what we've been pointed at is an Integer object, or
     * a method that will return an Integer.
     */
    buf.Pointer = &param;
    buf.Length = sizeof(param);
    status = AcpiEvaluateObject(handle, path, NULL, &buf);
    if (ACPI_SUCCESS(status)) {
	if (param.Type == ACPI_TYPE_INTEGER)
	    *number = param.Integer.Value;
	else
	    status = AE_TYPE;
    }

    /* 
     * In some applications, a method that's expected to return an Integer
     * may instead return a Buffer (probably to simplify some internal
     * arithmetic).  We'll try to fetch whatever it is, and if it's a Buffer,
     * convert it into an Integer as best we can.
     *
     * This is a hack.
     */
    if (status == AE_BUFFER_OVERFLOW) {
	if ((buf.Pointer = AcpiOsAllocate(buf.Length)) == NULL) {
	    status = AE_NO_MEMORY;
	} else {
	    status = AcpiEvaluateObject(handle, path, NULL, &buf);
	    if (ACPI_SUCCESS(status))
		status = acpi_ConvertBufferToInteger(&buf, number);
	    AcpiOsFree(buf.Pointer);
	}
    }
    return (status);
}