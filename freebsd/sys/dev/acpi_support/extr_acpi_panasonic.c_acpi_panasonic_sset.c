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
typedef  void* UINT64 ;
struct TYPE_5__ {void* Value; } ;
struct TYPE_7__ {TYPE_1__ Integer; void* Type; } ;
struct TYPE_6__ {int Count; TYPE_3__* Pointer; } ;
typedef  TYPE_2__ ACPI_OBJECT_LIST ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 void* ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panasonic ; 

__attribute__((used)) static void
acpi_panasonic_sset(ACPI_HANDLE h, UINT64 index, UINT64 val)
{
	ACPI_OBJECT_LIST args;
	ACPI_OBJECT obj[2];

	ACPI_SERIAL_ASSERT(panasonic);
	obj[0].Type = ACPI_TYPE_INTEGER;
	obj[0].Integer.Value = index;
	obj[1].Type = ACPI_TYPE_INTEGER;
	obj[1].Integer.Value = val;
	args.Count = 2;
	args.Pointer = obj;
	AcpiEvaluateObject(h, "SSET", &args, NULL);
}