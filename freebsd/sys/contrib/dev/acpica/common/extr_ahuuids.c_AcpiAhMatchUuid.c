#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
struct TYPE_3__ {char const* Description; int /*<<< orphan*/  String; } ;
typedef  TYPE_1__ AH_UUID ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiUtConvertStringToUuid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* Gbl_AcpiUuids ; 
 int UUID_BUFFER_LENGTH ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

const char *
AcpiAhMatchUuid (
    UINT8                   *Data)
{
    const AH_UUID           *Info;
    UINT8                   UuidBuffer[UUID_BUFFER_LENGTH];


    /* Walk the table of known ACPI-related UUIDs */

    for (Info = Gbl_AcpiUuids; Info->Description; Info++)
    {
        /* Null string means description is a UUID class */

        if (!Info->String)
        {
            continue;
        }

        AcpiUtConvertStringToUuid (Info->String, UuidBuffer);

        if (!memcmp (Data, UuidBuffer, UUID_BUFFER_LENGTH))
        {
            return (Info->Description);
        }
    }

    return (NULL);
}