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
struct TYPE_3__ {scalar_t__ Length; int /*<<< orphan*/  Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 scalar_t__ ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_ALLOCATE_LOCAL_BUFFER ; 
 scalar_t__ ACPI_NO_BUFFER ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 

ACPI_STATUS
AcpiUtValidateBuffer (
    ACPI_BUFFER             *Buffer)
{

    /* Obviously, the structure pointer must be valid */

    if (!Buffer)
    {
        return (AE_BAD_PARAMETER);
    }

    /* Special semantics for the length */

    if ((Buffer->Length == ACPI_NO_BUFFER)              ||
        (Buffer->Length == ACPI_ALLOCATE_BUFFER)        ||
        (Buffer->Length == ACPI_ALLOCATE_LOCAL_BUFFER))
    {
        return (AE_OK);
    }

    /* Length is valid, the buffer pointer must be also */

    if (!Buffer->Pointer)
    {
        return (AE_BAD_PARAMETER);
    }

    return (AE_OK);
}