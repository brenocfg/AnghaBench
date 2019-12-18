#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT64 ;
struct TYPE_4__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_5__ {TYPE_1__ Name; } ;
typedef  TYPE_2__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/ * ACPI_CAST_PTR (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ACPI_DEFAULT_RESNAME ; 
 int ACPI_NAMESEG_SIZE ; 
 size_t ACPI_NUM_RES_PREFIX ; 
 size_t AcpiGbl_NextPrefix ; 
 int AcpiGbl_NextResourceId ; 
 char* AcpiGbl_Prefix ; 
 char AcpiUtHexToAsciiChar (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  UINT32 ; 

__attribute__((used)) static void
AcpiDmUpdateResourceName (
    ACPI_NAMESPACE_NODE     *ResourceNode)
{
    char                    Name[ACPI_NAMESEG_SIZE];


    /* Ignore if a unique name has already been assigned */

    if (ResourceNode->Name.Integer != ACPI_DEFAULT_RESNAME)
    {
        return;
    }

    /* Generate a new ACPI name for the descriptor */

    Name[0] = '_';
    Name[1] = AcpiGbl_Prefix[AcpiGbl_NextPrefix];
    Name[2] = AcpiUtHexToAsciiChar ((UINT64) AcpiGbl_NextResourceId, 4);
    Name[3] = AcpiUtHexToAsciiChar ((UINT64) AcpiGbl_NextResourceId, 0);

    /* Update globals for next name */

    AcpiGbl_NextResourceId++;
    if (AcpiGbl_NextResourceId >= 256)
    {
        AcpiGbl_NextResourceId = 0;
        AcpiGbl_NextPrefix++;

        if (AcpiGbl_NextPrefix > ACPI_NUM_RES_PREFIX)
        {
            AcpiGbl_NextPrefix = 0;
        }
    }

    /* Change the resource descriptor name */

    ResourceNode->Name.Integer = *ACPI_CAST_PTR (UINT32, &Name[0]);
}