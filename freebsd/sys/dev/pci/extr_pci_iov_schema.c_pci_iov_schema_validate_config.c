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
typedef  int /*<<< orphan*/  uint16_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_CONFIG_NAME ; 
 int /*<<< orphan*/  pci_iov_config_get_num_vfs (int /*<<< orphan*/ *) ; 
 int pci_iov_schema_validate_device (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pci_iov_schema_validate_device_names (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pci_iov_schema_validate_vfs (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
pci_iov_schema_validate_config(const nvlist_t *schema, nvlist_t *config)
{
	int error;
	uint16_t num_vfs;

	error = pci_iov_schema_validate_device(schema, config, PF_CONFIG_NAME,
	    PF_CONFIG_NAME);
	if (error != 0)
		return (error);

	num_vfs = pci_iov_config_get_num_vfs(config);

	error = pci_iov_schema_validate_vfs(schema, config, num_vfs);
	if (error != 0)
		return (error);

	return (pci_iov_schema_validate_device_names(config, num_vfs));
}