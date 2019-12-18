#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  driver_t ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_10__ {scalar_t__ DutyWidth; } ;
struct TYPE_9__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_7__ {int PblkLength; scalar_t__ PblkAddress; } ;
struct TYPE_8__ {TYPE_1__ Processor; } ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PROCESSOR ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_5__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_2__*) ; 
 int /*<<< orphan*/ * BUS_ADD_CHILD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 scalar_t__ acpi_get_type (int /*<<< orphan*/ ) ; 
 scalar_t__ device_find_child (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
acpi_throttle_identify(driver_t *driver, device_t parent)
{
	ACPI_BUFFER buf;
	ACPI_HANDLE handle;
	ACPI_OBJECT *obj;

	/* Make sure we're not being doubly invoked. */
	if (device_find_child(parent, "acpi_throttle", -1))
		return;

	/* Check for a valid duty width and parent CPU type. */
	handle = acpi_get_handle(parent);
	if (handle == NULL)
		return;
	if (AcpiGbl_FADT.DutyWidth == 0 ||
	    acpi_get_type(parent) != ACPI_TYPE_PROCESSOR)
		return;

	/*
	 * Add a child if there's a non-NULL P_BLK and correct length, or
	 * if the _PTC method is present.
	 */
	buf.Pointer = NULL;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	if (ACPI_FAILURE(AcpiEvaluateObject(handle, NULL, NULL, &buf)))
		return;
	obj = (ACPI_OBJECT *)buf.Pointer;
	if ((obj->Processor.PblkAddress && obj->Processor.PblkLength >= 4) ||
	    ACPI_SUCCESS(AcpiEvaluateObject(handle, "_PTC", NULL, NULL))) {
		if (BUS_ADD_CHILD(parent, 0, "acpi_throttle", -1) == NULL)
			device_printf(parent, "add throttle child failed\n");
	}
	AcpiOsFree(obj);
}