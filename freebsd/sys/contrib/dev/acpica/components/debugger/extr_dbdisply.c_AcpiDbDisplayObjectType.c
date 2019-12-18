#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_11__ {size_t Count; TYPE_3__* Ids; } ;
struct TYPE_9__ {int /*<<< orphan*/  String; } ;
struct TYPE_8__ {int /*<<< orphan*/  String; } ;
struct TYPE_12__ {int Valid; TYPE_4__ CompatibleIdList; TYPE_2__ UniqueId; TYPE_1__ HardwareId; int /*<<< orphan*/ * LowestDstates; int /*<<< orphan*/ * HighestDstates; int /*<<< orphan*/  Flags; int /*<<< orphan*/  Address; } ;
struct TYPE_10__ {int /*<<< orphan*/  String; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_SIZE ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;
typedef  TYPE_5__ ACPI_DEVICE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 size_t ACPI_FORMAT_UINT64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_5__*) ; 
 int /*<<< orphan*/  ACPI_TO_POINTER (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_CID ; 
 int ACPI_VALID_HID ; 
 int ACPI_VALID_UID ; 
 int /*<<< orphan*/  AcpiFormatException (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGetObjectInfo (int /*<<< orphan*/ ,TYPE_5__**) ; 
 int /*<<< orphan*/  AcpiOsPrintf (char*,size_t,...) ; 
 int /*<<< orphan*/  strtoul (char*,int /*<<< orphan*/ *,int) ; 

void
AcpiDbDisplayObjectType (
    char                    *ObjectArg)
{
    ACPI_SIZE               Arg;
    ACPI_HANDLE             Handle;
    ACPI_DEVICE_INFO        *Info;
    ACPI_STATUS             Status;
    UINT32                  i;


    Arg = strtoul (ObjectArg, NULL, 16);
    Handle = ACPI_TO_POINTER (Arg);

    Status = AcpiGetObjectInfo (Handle, &Info);
    if (ACPI_FAILURE (Status))
    {
        AcpiOsPrintf ("Could not get object info, %s\n",
            AcpiFormatException (Status));
        return;
    }

    AcpiOsPrintf ("ADR: %8.8X%8.8X, Flags: %X\n",
        ACPI_FORMAT_UINT64 (Info->Address), Info->Flags);

    AcpiOsPrintf ("S1D-%2.2X S2D-%2.2X S3D-%2.2X S4D-%2.2X\n",
        Info->HighestDstates[0], Info->HighestDstates[1],
        Info->HighestDstates[2], Info->HighestDstates[3]);

    AcpiOsPrintf ("S0W-%2.2X S1W-%2.2X S2W-%2.2X S3W-%2.2X S4W-%2.2X\n",
        Info->LowestDstates[0], Info->LowestDstates[1],
        Info->LowestDstates[2], Info->LowestDstates[3],
        Info->LowestDstates[4]);

    if (Info->Valid & ACPI_VALID_HID)
    {
        AcpiOsPrintf ("HID: %s\n", Info->HardwareId.String);
    }

    if (Info->Valid & ACPI_VALID_UID)
    {
        AcpiOsPrintf ("UID: %s\n", Info->UniqueId.String);
    }

    if (Info->Valid & ACPI_VALID_CID)
    {
        for (i = 0; i < Info->CompatibleIdList.Count; i++)
        {
            AcpiOsPrintf ("CID %u: %s\n", i,
                Info->CompatibleIdList.Ids[i].String);
        }
    }

    ACPI_FREE (Info);
}