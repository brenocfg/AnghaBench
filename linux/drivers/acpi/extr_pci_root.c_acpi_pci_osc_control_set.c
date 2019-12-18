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
typedef  int u32 ;
struct acpi_pci_root {int osc_control_set; int osc_support_set; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 int /*<<< orphan*/  AE_TYPE ; 
 size_t OSC_CONTROL_DWORD ; 
 int OSC_PCI_CONTROL_MASKS ; 
 size_t OSC_QUERY_DWORD ; 
 size_t OSC_SUPPORT_DWORD ; 
 struct acpi_pci_root* acpi_pci_find_root (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_pci_query_osc (struct acpi_pci_root*,int,int*) ; 
 int /*<<< orphan*/  acpi_pci_run_osc (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  decode_osc_control (struct acpi_pci_root*,char*,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  osc_lock ; 

acpi_status acpi_pci_osc_control_set(acpi_handle handle, u32 *mask, u32 req)
{
	struct acpi_pci_root *root;
	acpi_status status = AE_OK;
	u32 ctrl, capbuf[3];

	if (!mask)
		return AE_BAD_PARAMETER;

	ctrl = *mask & OSC_PCI_CONTROL_MASKS;
	if ((ctrl & req) != req)
		return AE_TYPE;

	root = acpi_pci_find_root(handle);
	if (!root)
		return AE_NOT_EXIST;

	mutex_lock(&osc_lock);

	*mask = ctrl | root->osc_control_set;
	/* No need to evaluate _OSC if the control was already granted. */
	if ((root->osc_control_set & ctrl) == ctrl)
		goto out;

	/* Need to check the available controls bits before requesting them. */
	while (*mask) {
		status = acpi_pci_query_osc(root, root->osc_support_set, mask);
		if (ACPI_FAILURE(status))
			goto out;
		if (ctrl == *mask)
			break;
		decode_osc_control(root, "platform does not support",
				   ctrl & ~(*mask));
		ctrl = *mask;
	}

	if ((ctrl & req) != req) {
		decode_osc_control(root, "not requesting control; platform does not support",
				   req & ~(ctrl));
		status = AE_SUPPORT;
		goto out;
	}

	capbuf[OSC_QUERY_DWORD] = 0;
	capbuf[OSC_SUPPORT_DWORD] = root->osc_support_set;
	capbuf[OSC_CONTROL_DWORD] = ctrl;
	status = acpi_pci_run_osc(handle, capbuf, mask);
	if (ACPI_SUCCESS(status))
		root->osc_control_set = *mask;
out:
	mutex_unlock(&osc_lock);
	return status;
}