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
 int /*<<< orphan*/ * acpi_get_handle (int /*<<< orphan*/ ) ; 
 char* acpi_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcat (char*,char*,size_t) ; 
 int /*<<< orphan*/  uhub_child_location_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 

__attribute__((used)) static int
acpi_uhub_child_location_string(device_t parent, device_t child,
    char *buf, size_t buflen)
{
	ACPI_HANDLE ah;

	uhub_child_location_string(parent, child, buf, buflen);

	ah = acpi_get_handle(child);
	if (ah != NULL) {
		strlcat(buf, " handle=", buflen);
		strlcat(buf, acpi_name(ah), buflen);
	}
	return (0);
}