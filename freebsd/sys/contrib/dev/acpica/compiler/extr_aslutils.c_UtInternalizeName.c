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
struct TYPE_4__ {char* ExternalName; char* InternalName; int /*<<< orphan*/  Length; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_NAMESTRING_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsBuildInternalName (TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiNsGetInternalNameLength (TYPE_1__*) ; 
 char* UtLocalCacheCalloc (int /*<<< orphan*/ ) ; 

ACPI_STATUS
UtInternalizeName (
    char                    *ExternalName,
    char                    **ConvertedName)
{
    ACPI_NAMESTRING_INFO    Info;
    ACPI_STATUS             Status;


    if (!ExternalName)
    {
        return (AE_OK);
    }

    /* Get the length of the new internal name */

    Info.ExternalName = ExternalName;
    AcpiNsGetInternalNameLength (&Info);

    /* We need a segment to store the internal name */

    Info.InternalName = UtLocalCacheCalloc (Info.Length);

    /* Build the name */

    Status = AcpiNsBuildInternalName (&Info);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    *ConvertedName = Info.InternalName;
    return (AE_OK);
}