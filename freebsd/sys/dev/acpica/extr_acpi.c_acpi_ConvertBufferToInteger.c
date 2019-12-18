#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
typedef  int UINT32 ;
struct TYPE_9__ {scalar_t__ Pointer; } ;
struct TYPE_7__ {int Length; int* Pointer; } ;
struct TYPE_6__ {int Value; } ;
struct TYPE_8__ {scalar_t__ Type; TYPE_2__ Buffer; TYPE_1__ Integer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OBJECT ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  AE_BAD_DATA ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TYPE ; 

ACPI_STATUS
acpi_ConvertBufferToInteger(ACPI_BUFFER *bufp, UINT32 *number)
{
    ACPI_OBJECT	*p;
    UINT8	*val;
    int		i;

    p = (ACPI_OBJECT *)bufp->Pointer;
    if (p->Type == ACPI_TYPE_INTEGER) {
	*number = p->Integer.Value;
	return (AE_OK);
    }
    if (p->Type != ACPI_TYPE_BUFFER)
	return (AE_TYPE);
    if (p->Buffer.Length > sizeof(int))
	return (AE_BAD_DATA);

    *number = 0;
    val = p->Buffer.Pointer;
    for (i = 0; i < p->Buffer.Length; i++)
	*number += val[i] << (i * 8);
    return (AE_OK);
}