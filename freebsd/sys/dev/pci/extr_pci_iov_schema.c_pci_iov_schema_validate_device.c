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
 char const* DRIVER_CONFIG_NAME ; 
 int EINVAL ; 
 char const* IOV_CONFIG_NAME ; 
 int /*<<< orphan*/ * dnvlist_take_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int pci_iov_schema_validate_required (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int pci_iov_schema_validate_types (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pci_iov_schema_validate_device(const nvlist_t *schema, nvlist_t *config,
    const char *schema_device, const char *config_device)
{
	const nvlist_t *device_schema, *iov_schema, *driver_schema;
	nvlist_t *device_config, *iov_config, *driver_config;
	int error;

	device_config = NULL;
	iov_config = NULL;
	driver_config = NULL;

	device_schema = nvlist_get_nvlist(schema, schema_device);
	iov_schema = nvlist_get_nvlist(device_schema, IOV_CONFIG_NAME);
	driver_schema = nvlist_get_nvlist(device_schema, DRIVER_CONFIG_NAME);

	device_config = dnvlist_take_nvlist(config, config_device, NULL);
	if (device_config == NULL) {
		error = EINVAL;
		goto out;
	}

	iov_config = dnvlist_take_nvlist(device_config, IOV_CONFIG_NAME, NULL);
	if (iov_config == NULL) {
		error = EINVAL;
		goto out;
	}

	driver_config = dnvlist_take_nvlist(device_config, DRIVER_CONFIG_NAME,
	    NULL);
	if (driver_config == NULL) {
		error = EINVAL;
		goto out;
	}

	error = pci_iov_schema_validate_required(iov_schema, iov_config);
	if (error != 0)
		goto out;

	error = pci_iov_schema_validate_required(driver_schema, driver_config);
	if (error != 0)
		goto out;

	error = pci_iov_schema_validate_types(iov_schema, iov_config);
	if (error != 0)
		goto out;

	error = pci_iov_schema_validate_types(driver_schema, driver_config);
	if (error != 0)
		goto out;

out:
	/* Note that these functions handle NULL pointers safely. */
	nvlist_move_nvlist(device_config, IOV_CONFIG_NAME, iov_config);
	nvlist_move_nvlist(device_config, DRIVER_CONFIG_NAME, driver_config);
	nvlist_move_nvlist(config, config_device, device_config);

	return (error);
}