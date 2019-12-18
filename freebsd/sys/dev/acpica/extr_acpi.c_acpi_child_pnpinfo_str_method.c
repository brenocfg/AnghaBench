#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct acpi_device {int /*<<< orphan*/  ad_handle; } ;
typedef  int /*<<< orphan*/  device_t ;
struct TYPE_7__ {char* String; } ;
struct TYPE_6__ {int /*<<< orphan*/  String; } ;
struct TYPE_8__ {int Valid; TYPE_2__ HardwareId; TYPE_1__ UniqueId; } ;
typedef  TYPE_3__ ACPI_DEVICE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_VALID_HID ; 
 int ACPI_VALID_UID ; 
 int /*<<< orphan*/  AcpiGetObjectInfo (int /*<<< orphan*/ ,TYPE_3__**) ; 
 int /*<<< orphan*/  AcpiOsFree (TYPE_3__*) ; 
 struct acpi_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 unsigned long strtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
acpi_child_pnpinfo_str_method(device_t cbdev, device_t child, char *buf,
    size_t buflen)
{
    struct acpi_device *dinfo = device_get_ivars(child);
    ACPI_DEVICE_INFO *adinfo;

    if (ACPI_FAILURE(AcpiGetObjectInfo(dinfo->ad_handle, &adinfo))) {
	snprintf(buf, buflen, "unknown");
	return (0);
    }

    snprintf(buf, buflen, "_HID=%s _UID=%lu",
	(adinfo->Valid & ACPI_VALID_HID) ?
	adinfo->HardwareId.String : "none",
	(adinfo->Valid & ACPI_VALID_UID) ?
	strtoul(adinfo->UniqueId.String, NULL, 10) : 0UL);
    AcpiOsFree(adinfo);

    return (0);
}