#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/ * Elements; scalar_t__ Count; } ;
struct TYPE_10__ {int Value; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
union acpi_object {TYPE_3__ Package; void* Type; TYPE_2__ Integer; TYPE_1__ Buffer; } ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_13__ {int /*<<< orphan*/  Length; int /*<<< orphan*/ * Pointer; } ;
struct TYPE_12__ {int Count; union acpi_object* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_OBJECT_LIST ;
typedef  union acpi_object ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_5__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_BUFFER ; 
 void* ACPI_TYPE_INTEGER ; 
 void* ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  ACPI_UUID_LENGTH ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 

ACPI_STATUS
acpi_EvaluateDSM(ACPI_HANDLE handle, uint8_t *uuid, int revision,
    uint64_t function, union acpi_object *package, ACPI_BUFFER *out_buf)
{
    ACPI_OBJECT arg[4];
    ACPI_OBJECT_LIST arglist;
    ACPI_BUFFER buf;
    ACPI_STATUS status;

    if (out_buf == NULL)
	return (AE_NO_MEMORY);

    arg[0].Type = ACPI_TYPE_BUFFER;
    arg[0].Buffer.Length = ACPI_UUID_LENGTH;
    arg[0].Buffer.Pointer = uuid;
    arg[1].Type = ACPI_TYPE_INTEGER;
    arg[1].Integer.Value = revision;
    arg[2].Type = ACPI_TYPE_INTEGER;
    arg[2].Integer.Value = function;
    if (package) {
	arg[3] = *package;
    } else {
	arg[3].Type = ACPI_TYPE_PACKAGE;
	arg[3].Package.Count = 0;
	arg[3].Package.Elements = NULL;
    }

    arglist.Pointer = arg;
    arglist.Count = 4;
    buf.Pointer = NULL;
    buf.Length = ACPI_ALLOCATE_BUFFER;
    status = AcpiEvaluateObject(handle, "_DSM", &arglist, &buf);
    if (ACPI_FAILURE(status))
	return (status);

    KASSERT(ACPI_SUCCESS(status), ("Unexpected status"));

    *out_buf = buf;
    return (status);
}