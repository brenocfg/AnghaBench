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
 int /*<<< orphan*/  nvlist_exists_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int pci_iov_schema_validate_param (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_types(const nvlist_t *schema, const nvlist_t *config)
{
	const nvlist_t *schema_param;
	void *cookie;
	const char *name;
	int type, error;

	cookie = NULL;
	while ((name = nvlist_next(config, &type, &cookie)) != NULL) {
		if (!nvlist_exists_nvlist(schema, name))
			return (EINVAL);

		schema_param = nvlist_get_nvlist(schema, name);

		error = pci_iov_schema_validate_param(schema_param, name,
		    config);

		if (error != 0)
			return (error);
	}

	return (0);
}