#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT64 ;
struct TYPE_11__ {int /*<<< orphan*/ * Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_9__ {TYPE_2__* Elements; } ;
struct TYPE_10__ {scalar_t__ Type; TYPE_3__ Package; } ;
struct TYPE_7__ {size_t Value; } ;
struct TYPE_8__ {TYPE_1__ Integer; } ;
typedef  TYPE_4__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_5__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 int /*<<< orphan*/  ACPI_SERIAL_ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiOsFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panasonic ; 

__attribute__((used)) static UINT64
acpi_panasonic_sinf(ACPI_HANDLE h, UINT64 index)
{
	ACPI_BUFFER buf;
	ACPI_OBJECT *res;
	UINT64 ret;

	ACPI_SERIAL_ASSERT(panasonic);
	ret = -1;
	buf.Length = ACPI_ALLOCATE_BUFFER;
	buf.Pointer = NULL;
	AcpiEvaluateObject(h, "SINF", NULL, &buf);
	res = (ACPI_OBJECT *)buf.Pointer;
	if (res->Type == ACPI_TYPE_PACKAGE)
		ret = res->Package.Elements[index].Integer.Value;
	AcpiOsFree(buf.Pointer);

	return (ret);
}