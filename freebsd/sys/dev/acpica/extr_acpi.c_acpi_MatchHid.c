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
struct TYPE_9__ {int Count; TYPE_2__* Ids; } ;
struct TYPE_7__ {int /*<<< orphan*/  String; } ;
struct TYPE_10__ {int Valid; TYPE_3__ CompatibleIdList; TYPE_1__ HardwareId; } ;
struct TYPE_8__ {int /*<<< orphan*/  String; } ;
typedef  int BOOLEAN ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;
typedef  TYPE_4__ ACPI_DEVICE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_MATCHHID_CID ; 
 int ACPI_MATCHHID_HID ; 
 int ACPI_MATCHHID_NOMATCH ; 
 int ACPI_VALID_CID ; 
 int ACPI_VALID_HID ; 
 int /*<<< orphan*/  AcpiGetObjectInfo (int /*<<< orphan*/ *,TYPE_4__**) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_4__*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int
acpi_MatchHid(ACPI_HANDLE h, const char *hid) 
{
    ACPI_DEVICE_INFO	*devinfo;
    BOOLEAN		ret;
    int			i;

    if (hid == NULL || h == NULL ||
	ACPI_FAILURE(AcpiGetObjectInfo(h, &devinfo)))
	return (ACPI_MATCHHID_NOMATCH);

    ret = ACPI_MATCHHID_NOMATCH;
    if ((devinfo->Valid & ACPI_VALID_HID) != 0 &&
	strcmp(hid, devinfo->HardwareId.String) == 0)
	    ret = ACPI_MATCHHID_HID;
    else if ((devinfo->Valid & ACPI_VALID_CID) != 0)
	for (i = 0; i < devinfo->CompatibleIdList.Count; i++) {
	    if (strcmp(hid, devinfo->CompatibleIdList.Ids[i].String) == 0) {
		ret = ACPI_MATCHHID_CID;
		break;
	    }
	}

    AcpiOsFree(devinfo);
    return (ret);
}