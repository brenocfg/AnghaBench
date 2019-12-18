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
typedef  scalar_t__ UINT8 ;
struct TYPE_4__ {scalar_t__ Type; int Flags; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int ACPI_NS_DONT_OPEN_SCOPE ; 
 int ACPI_NS_ERROR_IF_FOUND ; 
 int ACPI_NS_EXTERNAL ; 
 int /*<<< orphan*/  AE_ERROR ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int ANOBJ_IS_EXTERNAL ; 
 int /*<<< orphan*/  AcpiNsLookup (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,TYPE_1__**) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDmResolveExternal (
    char                    *Path,
    UINT8                   Type,
    ACPI_NAMESPACE_NODE     **Node)
{
    ACPI_STATUS             Status;


    Status = AcpiNsLookup (NULL, Path, Type,
        ACPI_IMODE_LOAD_PASS1,
        ACPI_NS_ERROR_IF_FOUND | ACPI_NS_EXTERNAL | ACPI_NS_DONT_OPEN_SCOPE,
        NULL, Node);

    if (!Node)
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "while adding external to namespace [%s]", Path));
    }

    /* Note the asl code "external(a) external(a)" is acceptable ASL */

    else if ((*Node)->Type == Type &&
        (*Node)->Flags & ANOBJ_IS_EXTERNAL)
    {
        return (AE_OK);
    }
    else
    {
        ACPI_EXCEPTION ((AE_INFO, AE_ERROR,
            "[%s] has conflicting declarations", Path));
    }

    return (AE_ERROR);
}