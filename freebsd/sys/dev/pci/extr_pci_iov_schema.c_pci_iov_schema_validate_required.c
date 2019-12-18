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
typedef  int /*<<< orphan*/  const nvlist_t ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ dnvlist_get_bool (int /*<<< orphan*/  const*,char*,int /*<<< orphan*/ ) ; 
 int nvlist_error (int /*<<< orphan*/  const*) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  const* nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int /*<<< orphan*/  pci_iov_config_add_default (int /*<<< orphan*/  const*,char const*,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
pci_iov_schema_validate_required(const nvlist_t *schema, nvlist_t *config)
{
	const nvlist_t *param_schema;
	const char *name;
	void *cookie;
	int type;

	cookie = NULL;
	while ((name = nvlist_next(schema, &type, &cookie)) != NULL) {
		param_schema = nvlist_get_nvlist(schema, name);

		if (dnvlist_get_bool(param_schema, "required", 0)) {
			if (!nvlist_exists(config, name))
				return (EINVAL);
		}

		if (nvlist_exists(param_schema, "default") &&
		    !nvlist_exists(config, name))
			pci_iov_config_add_default(param_schema, name, config);
	}

	return (nvlist_error(config));
}