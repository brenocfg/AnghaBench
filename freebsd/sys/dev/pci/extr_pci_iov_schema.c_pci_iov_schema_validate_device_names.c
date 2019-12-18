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
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int pci_iov_schema_validate_dev_name (char const*,int /*<<< orphan*/ ) ; 
 int pci_iov_schema_validate_device_subsystems (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_device_names(const nvlist_t *config, uint16_t num_vfs)
{
	const nvlist_t *device;
	void *cookie;
	const char *name;
	int type, error;

	cookie = NULL;
	while ((name = nvlist_next(config, &type, &cookie)) != NULL) {
		error = pci_iov_schema_validate_dev_name(name, num_vfs);
		if (error != 0)
			return (error);

		/*
		 * Note that as this is a valid PF/VF node, we know that
		 * pci_iov_schema_validate_device() has already checked that
		 * the PF/VF node is an nvlist.
		 */
		device = nvlist_get_nvlist(config, name);
		error = pci_iov_schema_validate_device_subsystems(device);
		if (error != 0)
			return (error);
	}

	return (0);
}