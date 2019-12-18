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
 scalar_t__ nvlist_exists (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 

__attribute__((used)) static int
pci_iov_validate_param_collisions(const nvlist_t *dev_schema)
{
	const nvlist_t *iov_schema, *driver_schema;
	const char *name;
	void *it;
	int type;

	driver_schema = nvlist_get_nvlist(dev_schema, DRIVER_CONFIG_NAME);
	iov_schema = nvlist_get_nvlist(dev_schema, IOV_CONFIG_NAME);

	it = NULL;
	while ((name = nvlist_next(driver_schema, &type, &it)) != NULL) {
		if (nvlist_exists(iov_schema, name))
			return (EINVAL);
	}

	return (0);
}