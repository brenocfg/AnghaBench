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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_CONFIG_NAME ; 
 int /*<<< orphan*/  VF_SCHEMA_NAME ; 
 int pci_iov_validate_device_schema (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int pci_iov_validate_schema_devices (int /*<<< orphan*/  const*) ; 

int
pci_iov_validate_schema(const nvlist_t *schema)
{
	int error;

	error = pci_iov_validate_device_schema(schema, PF_CONFIG_NAME);
	if (error != 0)
		return (error);

	error = pci_iov_validate_device_schema(schema, VF_SCHEMA_NAME);
	if (error != 0)
		return (error);

	return (pci_iov_validate_schema_devices(schema));
}