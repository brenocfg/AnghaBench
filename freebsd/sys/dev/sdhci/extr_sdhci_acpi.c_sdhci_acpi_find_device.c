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
struct sdhci_acpi_device {int uid; int /*<<< orphan*/ * hid; } ;
typedef  int /*<<< orphan*/  device_t ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_ID_PROBE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  acpi_GetInteger (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_parent (int /*<<< orphan*/ ) ; 
 struct sdhci_acpi_device const* sdhci_acpi_devices ; 
 int /*<<< orphan*/  sdhci_ids ; 
 scalar_t__ strcmp (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static const struct sdhci_acpi_device *
sdhci_acpi_find_device(device_t dev)
{
	char *hid;
	int i, uid;
	ACPI_HANDLE handle;
	ACPI_STATUS status;
	int rv;

	rv = ACPI_ID_PROBE(device_get_parent(dev), dev, sdhci_ids, &hid);
	if (rv > 0)
		return (NULL);

	handle = acpi_get_handle(dev);
	status = acpi_GetInteger(handle, "_UID", &uid);
	if (ACPI_FAILURE(status))
		uid = 0;

	for (i = 0; sdhci_acpi_devices[i].hid != NULL; i++) {
		if (strcmp(sdhci_acpi_devices[i].hid, hid) != 0)
			continue;
		if ((sdhci_acpi_devices[i].uid != 0) &&
		    (sdhci_acpi_devices[i].uid != uid))
			continue;
		return (&sdhci_acpi_devices[i]);
	}

	return (NULL);
}