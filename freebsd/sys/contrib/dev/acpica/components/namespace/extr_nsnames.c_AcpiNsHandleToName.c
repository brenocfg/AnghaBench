#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ Pointer; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_1__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_COPY_NAMESEG (scalar_t__,char const*) ; 
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ACPI_NAMESEG_SIZE ; 
 int /*<<< orphan*/  ACPI_PATH_SEGMENT_LENGTH ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * AcpiNsValidateHandle (int /*<<< orphan*/ ) ; 
 char* AcpiUtGetNodeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtInitializeBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NsHandleToName ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiNsHandleToName (
    ACPI_HANDLE             TargetHandle,
    ACPI_BUFFER             *Buffer)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;
    const char              *NodeName;


    ACPI_FUNCTION_TRACE_PTR (NsHandleToName, TargetHandle);


    Node = AcpiNsValidateHandle (TargetHandle);
    if (!Node)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Validate/Allocate/Clear caller buffer */

    Status = AcpiUtInitializeBuffer (Buffer, ACPI_PATH_SEGMENT_LENGTH);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Just copy the ACPI name from the Node and zero terminate it */

    NodeName = AcpiUtGetNodeName (Node);
    ACPI_COPY_NAMESEG (Buffer->Pointer, NodeName);
    ((char *) Buffer->Pointer) [ACPI_NAMESEG_SIZE] = 0;

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "%4.4s\n", (char *) Buffer->Pointer));
    return_ACPI_STATUS (AE_OK);
}