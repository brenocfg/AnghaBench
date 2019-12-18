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
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmCreateSubobjectForExternal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDmResolveExternal (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

void
AcpiDmAddOneExternalToNamespace (
    char                    *Path,
    UINT8                   Type,
    UINT32                  ParamCount)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;


    Status = AcpiDmResolveExternal (Path, Type, &Node);

    if (ACPI_FAILURE (Status))
    {
        return;
    }

    AcpiDmCreateSubobjectForExternal (Type, &Node, ParamCount);

}