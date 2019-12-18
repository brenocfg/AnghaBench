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
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/ * ACPI_HANDLE ;

/* Variables and functions */
 int EOVERFLOW ; 
 char* acpi_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvdimm_root_get_acpi_handle (int /*<<< orphan*/ ) ; 
 int snprintf (char*,size_t,char*,...) ; 

__attribute__((used)) static int
nvdimm_root_child_location_str(device_t dev, device_t child, char *buf,
    size_t buflen)
{
	ACPI_HANDLE handle;
	int res;

	handle = nvdimm_root_get_acpi_handle(child);
	if (handle != NULL)
		res = snprintf(buf, buflen, "handle=%s", acpi_name(handle));
	else
		res = snprintf(buf, buflen, "");

	if (res >= buflen)
		return (EOVERFLOW);
	return (0);
}