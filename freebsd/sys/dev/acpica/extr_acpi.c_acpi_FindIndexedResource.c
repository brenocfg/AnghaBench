#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int8_t ;
struct TYPE_8__ {int Length; scalar_t__ Pointer; } ;
struct TYPE_7__ {scalar_t__ Type; scalar_t__ Length; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_RESOURCE ;
typedef  TYPE_2__ ACPI_BUFFER ;

/* Variables and functions */
 TYPE_1__* ACPI_NEXT_RESOURCE (TYPE_1__*) ; 
 scalar_t__ ACPI_RESOURCE_TYPE_END_TAG ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NOT_FOUND ; 
 int /*<<< orphan*/  AE_OK ; 

ACPI_STATUS
acpi_FindIndexedResource(ACPI_BUFFER *buf, int index, ACPI_RESOURCE **resp)
{
    ACPI_RESOURCE	*rp;
    int			i;

    rp = (ACPI_RESOURCE *)buf->Pointer;
    i = index;
    while (i-- > 0) {
	/* Range check */
	if (rp > (ACPI_RESOURCE *)((u_int8_t *)buf->Pointer + buf->Length))
	    return (AE_BAD_PARAMETER);

	/* Check for terminator */
	if (rp->Type == ACPI_RESOURCE_TYPE_END_TAG || rp->Length == 0)
	    return (AE_NOT_FOUND);
	rp = ACPI_NEXT_RESOURCE(rp);
    }
    if (resp != NULL)
	*resp = rp;

    return (AE_OK);
}