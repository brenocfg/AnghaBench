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
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcasecmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_iov_schema_validate_device_subsystems(const nvlist_t *config)
{
	void *cookie;
	const char *name;
	int type;

	cookie = NULL;
	while ((name = nvlist_next(config, &type, &cookie)) != NULL) {
		if (strcasecmp(name, IOV_CONFIG_NAME) == 0)
			continue;
		else if (strcasecmp(name, DRIVER_CONFIG_NAME) == 0)
			continue;

		return (EINVAL);
	}

	return (0);
}