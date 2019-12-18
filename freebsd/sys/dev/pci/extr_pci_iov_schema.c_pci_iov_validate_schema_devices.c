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
 int EINVAL ; 
 int /*<<< orphan*/  PF_CONFIG_NAME ; 
 int /*<<< orphan*/  VF_SCHEMA_NAME ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
pci_iov_validate_schema_devices(const nvlist_t *dev_schema)
{
	const char *name;
	void *it;
	int type;

	it = NULL;
	while ((name = nvlist_next(dev_schema, &type, &it)) != NULL) {
		if (strcmp(name, PF_CONFIG_NAME) != 0 &&
		    strcmp(name, VF_SCHEMA_NAME) != 0)
			return (EINVAL);
	}

	return (0);
}