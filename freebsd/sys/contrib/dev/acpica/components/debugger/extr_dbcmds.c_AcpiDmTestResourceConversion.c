#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_2__* Pointer; void* Length; } ;
struct TYPE_10__ {scalar_t__ Length; int /*<<< orphan*/  Pointer; } ;
struct TYPE_11__ {TYPE_1__ Buffer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_RSDESC_SIZE ;
typedef  TYPE_2__ ACPI_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_3__ ACPI_BUFFER ;

/* Variables and functions */
 void* ACPI_ALLOCATE_LOCAL_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDmCompareAmlResources (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetCurrentResources (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 int /*<<< orphan*/  AcpiRsCreateAmlResources (TYPE_3__*,TYPE_3__*) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmTestResourceConversion (
    ACPI_NAMESPACE_NODE     *Node,
    char                    *Name)
{
    ACPI_STATUS             Status;
    ACPI_BUFFER             ReturnBuffer;
    ACPI_BUFFER             ResourceBuffer;
    ACPI_BUFFER             NewAml;
    ACPI_OBJECT             *OriginalAml;


    AcpiOsPrintf ("Resource Conversion Comparison:\n");

    NewAml.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    ReturnBuffer.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    ResourceBuffer.Length = ACPI_ALLOCATE_LOCAL_BUFFER;

    /* Get the original _CRS AML resource template */

    Status = AcpiEvaluateObject (Node, Name, NULL, &ReturnBuffer);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not obtain %s: %s\n",
            Name, AcpiFormatException (Status));
        return (Status);
    }

    /* Get the AML resource template, converted to internal resource structs */

    Status = AcpiGetCurrentResources (Node, &ResourceBuffer);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("AcpiGetCurrentResources failed: %s\n",
            AcpiFormatException (Status));
        goto Exit1;
    }

    /* Convert internal resource list to external AML resource template */

    Status = AcpiRsCreateAmlResources (&ResourceBuffer, &NewAml);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("AcpiRsCreateAmlResources failed: %s\n",
            AcpiFormatException (Status));
        goto Exit2;
    }

    /* Compare original AML to the newly created AML resource list */

    OriginalAml = ReturnBuffer.Pointer;

    AcpiDmCompareAmlResources (OriginalAml->Buffer.Pointer,
        (ACPI_RSDESC_SIZE) OriginalAml->Buffer.Length,
        NewAml.Pointer, (ACPI_RSDESC_SIZE) NewAml.Length);

    /* Cleanup and exit */

    ACPI_FREE (NewAml.Pointer);
Exit2:
    ACPI_FREE (ResourceBuffer.Pointer);
Exit1:
    ACPI_FREE (ReturnBuffer.Pointer);
    return (Status);
}