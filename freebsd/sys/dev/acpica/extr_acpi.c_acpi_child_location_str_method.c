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
struct acpi_device {scalar_t__ ad_handle; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_GetInteger (scalar_t__,char*,int*) ; 
 char* acpi_name (scalar_t__) ; 
 struct acpi_device* device_get_ivars (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,...) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 

__attribute__((used)) static int
acpi_child_location_str_method(device_t cbdev, device_t child, char *buf,
    size_t buflen)
{
    struct acpi_device *dinfo = device_get_ivars(child);
    char buf2[32];
    int pxm;

    if (dinfo->ad_handle) {
        snprintf(buf, buflen, "handle=%s", acpi_name(dinfo->ad_handle));
        if (ACPI_SUCCESS(acpi_GetInteger(dinfo->ad_handle, "_PXM", &pxm))) {
                snprintf(buf2, 32, " _PXM=%d", pxm);
                strlcat(buf, buf2, buflen);
        }
    } else {
        snprintf(buf, buflen, "");
    }
    return (0);
}