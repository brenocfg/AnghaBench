#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int UINT32 ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int ACPI_TYPE_NS_NODE_MAX ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AcpiDbClassifyOneObject ; 
 scalar_t__* AcpiGbl_NodeTypeCount ; 
 scalar_t__ AcpiGbl_NumNodes ; 
 scalar_t__ AcpiGbl_NumObjects ; 
 scalar_t__* AcpiGbl_ObjTypeCount ; 
 scalar_t__ AcpiGbl_ObjTypeCountMisc ; 
 int /*<<< orphan*/  AcpiNsWalkNamespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 

__attribute__((used)) static void
AcpiDbCountNamespaceObjects (
    void)
{
    UINT32                  i;


    AcpiGbl_NumNodes = 0;
    AcpiGbl_NumObjects = 0;

    AcpiGbl_ObjTypeCountMisc = 0;
    for (i = 0; i < (ACPI_TYPE_NS_NODE_MAX -1); i++)
    {
        AcpiGbl_ObjTypeCount [i] = 0;
        AcpiGbl_NodeTypeCount [i] = 0;
    }

    (void) AcpiNsWalkNamespace (ACPI_TYPE_ANY, ACPI_ROOT_OBJECT,
        ACPI_UINT32_MAX, FALSE, AcpiDbClassifyOneObject, NULL, NULL, NULL);
}