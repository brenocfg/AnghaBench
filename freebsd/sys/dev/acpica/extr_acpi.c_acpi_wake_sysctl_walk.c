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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiEvaluateObject (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  M_TEMP ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_CHILDREN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_get_handle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_wake_set_sysctl ; 
 int device_get_children (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  device_get_sysctl_ctx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_get_sysctl_tree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_is_attached (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
acpi_wake_sysctl_walk(device_t dev)
{
    int error, i, numdevs;
    device_t *devlist;
    device_t child;
    ACPI_STATUS status;

    error = device_get_children(dev, &devlist, &numdevs);
    if (error != 0 || numdevs == 0) {
	if (numdevs == 0)
	    free(devlist, M_TEMP);
	return (error);
    }
    for (i = 0; i < numdevs; i++) {
	child = devlist[i];
	acpi_wake_sysctl_walk(child);
	if (!device_is_attached(child))
	    continue;
	status = AcpiEvaluateObject(acpi_get_handle(child), "_PRW", NULL, NULL);
	if (ACPI_SUCCESS(status)) {
	    SYSCTL_ADD_PROC(device_get_sysctl_ctx(child),
		SYSCTL_CHILDREN(device_get_sysctl_tree(child)), OID_AUTO,
		"wake", CTLTYPE_INT | CTLFLAG_RW, child, 0,
		acpi_wake_set_sysctl, "I", "Device set to wake the system");
	}
    }
    free(devlist, M_TEMP);

    return (0);
}