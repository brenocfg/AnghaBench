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
 int /*<<< orphan*/  DRIVER_CONFIG_NAME ; 
 int EINVAL ; 
 int /*<<< orphan*/  IOV_CONFIG_NAME ; 
 int /*<<< orphan*/  nvlist_exists_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 int pci_iov_validate_param_collisions (int /*<<< orphan*/  const*) ; 
 int pci_iov_validate_schema_subsystems (int /*<<< orphan*/  const*) ; 
 int pci_iov_validate_subsystem_schema (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_iov_validate_device_schema(const nvlist_t *schema, const char *name)
{
	const nvlist_t *dev_schema;
	int error;

	if (!nvlist_exists_nvlist(schema, name))
		return (EINVAL);
	dev_schema = nvlist_get_nvlist(schema, name);

	error = pci_iov_validate_subsystem_schema(dev_schema, IOV_CONFIG_NAME);
	if (error != 0)
		return (error);

	error = pci_iov_validate_subsystem_schema(dev_schema,
	    DRIVER_CONFIG_NAME);
	if (error != 0)
		return (error);

	error = pci_iov_validate_param_collisions(dev_schema);
	if (error != 0)
		return (error);

	return (pci_iov_validate_schema_subsystems(dev_schema));
}