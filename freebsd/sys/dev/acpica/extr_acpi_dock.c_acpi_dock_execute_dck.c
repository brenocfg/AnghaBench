#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  retobj ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {int Length; TYPE_3__* Pointer; } ;
struct TYPE_7__ {int Value; } ;
struct TYPE_9__ {scalar_t__ Type; TYPE_1__ Integer; } ;
struct TYPE_8__ {int Count; TYPE_3__* Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int ACPI_DOCK_ISOLATE ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,TYPE_2__*,TYPE_4__*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_dock_execute_dck(device_t dev, int dock)
{
	ACPI_HANDLE	h;
	ACPI_OBJECT	argobj;
	ACPI_OBJECT_LIST args;
	ACPI_BUFFER	buf;
	ACPI_OBJECT	retobj;
	ACPI_STATUS	status;

	h = acpi_get_handle(dev);

	argobj.Type = ACPI_TYPE_INTEGER;
	argobj.Integer.Value = dock;
	args.Count = 1;
	args.Pointer = &argobj;
	buf.Pointer = &retobj;
	buf.Length = sizeof(retobj);
	status = AcpiEvaluateObject(h, "_DCK", &args, &buf);

	/*
	 * When _DCK is called with 0, OSPM will ignore the return value.
	 */
	if (dock == ACPI_DOCK_ISOLATE)
		return (0);

	/* If _DCK returned 1, the request succeeded. */
	if (ACPI_SUCCESS(status) && retobj.Type == ACPI_TYPE_INTEGER &&
	    retobj.Integer.Value == 1)
		return (0);

	return (-1);
}