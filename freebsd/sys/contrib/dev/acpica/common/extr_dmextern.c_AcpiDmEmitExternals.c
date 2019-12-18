#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ Type; int Flags; struct TYPE_5__* Path; struct TYPE_5__* InternalPath; struct TYPE_5__* Next; int /*<<< orphan*/  Value; } ;
typedef  TYPE_1__ ACPI_EXTERNAL_LIST ;

/* Variables and functions */
 int ACPI_EXT_CONFLICTING_DECLARATION ; 
 int ACPI_EXT_EXTERNAL_EMITTED ; 
 int ACPI_EXT_INTERNAL_PATH_ALLOCATED ; 
 int ACPI_EXT_ORIGIN_FROM_FILE ; 
 int ACPI_EXT_RESOLVED_REFERENCE ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 scalar_t__ ACPI_TYPE_METHOD ; 
 int /*<<< orphan*/  AcpiDmConflictingDeclaration (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiDmGetObjectTypeName (scalar_t__) ; 
 int /*<<< orphan*/  AcpiDmUnresolvedWarning (int) ; 
 TYPE_1__* AcpiGbl_ExternalList ; 
 int /*<<< orphan*/  AcpiGbl_NumExternalMethods ; 
 int /*<<< orphan*/  AcpiGbl_ResolvedExternalMethods ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,...) ; 
 scalar_t__ AslGbl_ExternalRefFilename ; 
 int /*<<< orphan*/  ExternalConflictMessage ; 

void
AcpiDmEmitExternals (
    void)
{
    ACPI_EXTERNAL_LIST      *NextExternal;


    if (!AcpiGbl_ExternalList)
    {
        return;
    }

    /*
     * Determine the number of control methods in the external list, and
     * also how many of those externals were resolved via the namespace.
     */
    NextExternal = AcpiGbl_ExternalList;
    while (NextExternal)
    {
        if (NextExternal->Type == ACPI_TYPE_METHOD)
        {
            AcpiGbl_NumExternalMethods++;
            if (NextExternal->Flags & ACPI_EXT_RESOLVED_REFERENCE)
            {
                AcpiGbl_ResolvedExternalMethods++;
            }
        }

        NextExternal = NextExternal->Next;
    }

    /* Check if any control methods were unresolved */

    AcpiDmUnresolvedWarning (1);

    if (AslGbl_ExternalRefFilename)
    {
        AcpiOsPrintf (
            "    /*\n     * External declarations were imported from\n"
            "     * a reference file -- %s\n     */\n\n",
            AslGbl_ExternalRefFilename);
    }

    /*
     * Walk and emit the list of externals found during the AML parsing
     */
    while (AcpiGbl_ExternalList)
    {
        if (!(AcpiGbl_ExternalList->Flags & ACPI_EXT_EXTERNAL_EMITTED))
        {
            AcpiOsPrintf ("    External (%s%s)",
                AcpiGbl_ExternalList->Path,
                AcpiDmGetObjectTypeName (AcpiGbl_ExternalList->Type));

            /* Check for "unresolved" method reference */

            if ((AcpiGbl_ExternalList->Type == ACPI_TYPE_METHOD) &&
                (!(AcpiGbl_ExternalList->Flags & ACPI_EXT_RESOLVED_REFERENCE)))
            {
                AcpiOsPrintf ("    // Warning: Unknown method, "
                    "guessing %u arguments",
                    AcpiGbl_ExternalList->Value);
            }

            /* Check for external from a external references file */

            else if (AcpiGbl_ExternalList->Flags & ACPI_EXT_ORIGIN_FROM_FILE)
            {
                if (AcpiGbl_ExternalList->Type == ACPI_TYPE_METHOD)
                {
                    AcpiOsPrintf ("    // %u Arguments",
                        AcpiGbl_ExternalList->Value);
                }

                AcpiOsPrintf ("    // From external reference file");
            }

            /* This is the normal external case */

            else
            {
                /* For methods, add a comment with the number of arguments */

                if (AcpiGbl_ExternalList->Type == ACPI_TYPE_METHOD)
                {
                    AcpiOsPrintf ("    // %u Arguments",
                        AcpiGbl_ExternalList->Value);
                }
            }

            if (AcpiGbl_ExternalList->Flags &= ACPI_EXT_CONFLICTING_DECLARATION)
            {
                AcpiOsPrintf ("%s", ExternalConflictMessage);
                AcpiDmConflictingDeclaration (AcpiGbl_ExternalList->Path);
            }
            AcpiOsPrintf ("\n");
        }

        /* Free this external info block and move on to next external */

        NextExternal = AcpiGbl_ExternalList->Next;
        if (AcpiGbl_ExternalList->Flags & ACPI_EXT_INTERNAL_PATH_ALLOCATED)
        {
            ACPI_FREE (AcpiGbl_ExternalList->InternalPath);
        }

        ACPI_FREE (AcpiGbl_ExternalList->Path);
        ACPI_FREE (AcpiGbl_ExternalList);
        AcpiGbl_ExternalList = NextExternal;
    }

    AcpiOsPrintf ("\n");
}