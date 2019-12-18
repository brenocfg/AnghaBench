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
struct TYPE_4__ {char* Path; struct TYPE_4__* Next; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_EXTERNAL_FILE ;

/* Variables and functions */
 char* ACPI_ALLOCATE (scalar_t__) ; 
 TYPE_1__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_FREE (char*) ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* AcpiGbl_ExternalFileList ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 

ACPI_STATUS
AcpiDmAddToExternalFileList (
    char                    *Pathname)
{
    ACPI_EXTERNAL_FILE      *ExternalFile;
    char                    *LocalPathname;


    if (!Pathname)
    {
        return (AE_OK);
    }

    LocalPathname = ACPI_ALLOCATE (strlen (Pathname) + 1);
    if (!LocalPathname)
    {
        return (AE_NO_MEMORY);
    }

    ExternalFile = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_EXTERNAL_FILE));
    if (!ExternalFile)
    {
        ACPI_FREE (LocalPathname);
        return (AE_NO_MEMORY);
    }

    /* Take a copy of the file pathname */

    strcpy (LocalPathname, Pathname);
    ExternalFile->Path = LocalPathname;

    if (AcpiGbl_ExternalFileList)
    {
        ExternalFile->Next = AcpiGbl_ExternalFileList;
    }

    AcpiGbl_ExternalFileList = ExternalFile;
    return (AE_OK);
}