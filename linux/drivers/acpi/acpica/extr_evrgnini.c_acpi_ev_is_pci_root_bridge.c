#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  size_t u32 ;
struct acpi_pnp_device_id_list {size_t count; TYPE_1__* ids; int /*<<< orphan*/  string; } ;
struct acpi_pnp_device_id {size_t count; TYPE_1__* ids; int /*<<< orphan*/  string; } ;
struct acpi_namespace_node {int dummy; } ;
typedef  int /*<<< orphan*/  acpi_status ;
struct TYPE_2__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (struct acpi_pnp_device_id_list*) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  acpi_ut_execute_CID (struct acpi_namespace_node*,struct acpi_pnp_device_id_list**) ; 
 int /*<<< orphan*/  acpi_ut_execute_HID (struct acpi_namespace_node*,struct acpi_pnp_device_id_list**) ; 
 scalar_t__ acpi_ut_is_pci_root_bridge (int /*<<< orphan*/ ) ; 

u8 acpi_ev_is_pci_root_bridge(struct acpi_namespace_node *node)
{
	acpi_status status;
	struct acpi_pnp_device_id *hid;
	struct acpi_pnp_device_id_list *cid;
	u32 i;
	u8 match;

	/* Get the _HID and check for a PCI Root Bridge */

	status = acpi_ut_execute_HID(node, &hid);
	if (ACPI_FAILURE(status)) {
		return (FALSE);
	}

	match = acpi_ut_is_pci_root_bridge(hid->string);
	ACPI_FREE(hid);

	if (match) {
		return (TRUE);
	}

	/* The _HID did not match. Get the _CID and check for a PCI Root Bridge */

	status = acpi_ut_execute_CID(node, &cid);
	if (ACPI_FAILURE(status)) {
		return (FALSE);
	}

	/* Check all _CIDs in the returned list */

	for (i = 0; i < cid->count; i++) {
		if (acpi_ut_is_pci_root_bridge(cid->ids[i].string)) {
			ACPI_FREE(cid);
			return (TRUE);
		}
	}

	ACPI_FREE(cid);
	return (FALSE);
}