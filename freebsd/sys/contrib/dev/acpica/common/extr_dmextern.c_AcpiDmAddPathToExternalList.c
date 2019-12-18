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
typedef  int UINT16 ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int ACPI_EXT_INTERNAL_PATH_ALLOCATED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 char AML_ROOT_PREFIX ; 
 int /*<<< orphan*/  AcpiDmCreateNewExternal (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  AcpiNsExternalizeName (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  AcpiNsInternalizeName (char*,char**) ; 
 int /*<<< orphan*/  DmAddPathToExternalList ; 
 int /*<<< orphan*/  return_VOID ; 

__attribute__((used)) static void
AcpiDmAddPathToExternalList (
    char                    *Path,
    UINT8                   Type,
    UINT32                  Value,
    UINT16                  Flags)
{
    char                    *InternalPath;
    char                    *ExternalPath;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (DmAddPathToExternalList);


    if (!Path)
    {
        return_VOID;
    }

    /* Remove a root backslash if present */

    if ((*Path == AML_ROOT_PREFIX) && (Path[1]))
    {
        Path++;
    }

    /* Create the internal and external pathnames */

    Status = AcpiNsInternalizeName (Path, &InternalPath);
    if (ACPI_FAILURE (Status))
    {
        return_VOID;
    }

    Status = AcpiNsExternalizeName (ACPI_UINT32_MAX, InternalPath,
        NULL, &ExternalPath);
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (InternalPath);
        return_VOID;
    }

    /* Create the new External() declaration node */

    Status = AcpiDmCreateNewExternal (ExternalPath, InternalPath,
        Type, Value, (Flags | ACPI_EXT_INTERNAL_PATH_ALLOCATED));
    if (ACPI_FAILURE (Status))
    {
        ACPI_FREE (ExternalPath);
        ACPI_FREE (InternalPath);
    }

    return_VOID;
}