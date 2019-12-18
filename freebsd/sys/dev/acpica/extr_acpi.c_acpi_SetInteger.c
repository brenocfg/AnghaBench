#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_5__ {int /*<<< orphan*/  Value; } ;
struct TYPE_7__ {TYPE_1__ Integer; int /*<<< orphan*/  Type; } ;
struct TYPE_6__ {int Count; TYPE_3__* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ *) ; 

ACPI_STATUS
acpi_SetInteger(ACPI_HANDLE handle, char *path, UINT32 number)
{
    ACPI_OBJECT arg1;
    ACPI_OBJECT_LIST args;

    arg1.Type = ACPI_TYPE_INTEGER;
    arg1.Integer.Value = number;
    args.Count = 1;
    args.Pointer = &arg1;

    return (AcpiEvaluateObject(handle, path, &args, NULL));
}