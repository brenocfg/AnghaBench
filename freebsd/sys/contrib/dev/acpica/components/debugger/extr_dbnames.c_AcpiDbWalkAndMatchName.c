#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_10__ {scalar_t__ Pointer; int /*<<< orphan*/  Length; } ;
struct TYPE_7__ {char* Ascii; } ;
struct TYPE_9__ {TYPE_1__ Name; } ;
struct TYPE_8__ {int DisplayType; int /*<<< orphan*/  DebugLevel; int /*<<< orphan*/  OwnerId; scalar_t__ Count; } ;
typedef  TYPE_2__ ACPI_WALK_INFO ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;
typedef  char* ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_BUFFER ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_LOCAL_BUFFER ; 
 int ACPI_DISPLAY_SHORT ; 
 int ACPI_DISPLAY_SUMMARY ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_OWNER_ID_MAX ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsDumpOneObject (char*,int,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiNsHandleToPathname (char*,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,char*) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static ACPI_STATUS
AcpiDbWalkAndMatchName (
    ACPI_HANDLE             ObjHandle,
    UINT32                  NestingLevel,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_STATUS             Status;
    char                    *RequestedName = (char *) Context;
    UINT32                  i;
    ACPI_BUFFER             Buffer;
    ACPI_WALK_INFO          Info;


    /* Check for a name match */

    for (i = 0; i < 4; i++)
    {
        /* Wildcard support */

        if ((RequestedName[i] != '?') &&
            (RequestedName[i] != ((ACPI_NAMESPACE_NODE *)
                ObjHandle)->Name.Ascii[i]))
        {
            /* No match, just exit */

            return (AE_OK);
        }
    }

    /* Get the full pathname to this object */

    Buffer.Length = ACPI_ALLOCATE_LOCAL_BUFFER;
    Status = AcpiNsHandleToPathname (ObjHandle, &Buffer, TRUE);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could Not get pathname for object %p\n",
            ObjHandle);
    }
    else
    {
        Info.Count = 0;
        Info.OwnerId = ACPI_OWNER_ID_MAX;
        Info.DebugLevel = ACPI_UINT32_MAX;
        Info.DisplayType = ACPI_DISPLAY_SUMMARY | ACPI_DISPLAY_SHORT;

        AcpiOsPrintf ("%32s", (char *) Buffer.Pointer);
        (void) AcpiNsDumpOneObject (ObjHandle, NestingLevel, &Info, NULL);
        ACPI_FREE (Buffer.Pointer);
    }

    return (AE_OK);
}