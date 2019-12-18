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
 int /*<<< orphan*/  REQUIRED_SCHEMA_NAME ; 
 scalar_t__ dnvlist_get_bool (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errx (int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  nvlist_exists (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 

__attribute__((used)) static void
validate_subsystem(const nvlist_t *device, const nvlist_t *device_schema,
    const char *subsystem_name, const char *config_name)
{
	const nvlist_t *subsystem, *schema, *config;
	const char *name;
	void *cookie;
	int type;

	subsystem = nvlist_get_nvlist(device, subsystem_name);
	schema = nvlist_get_nvlist(device_schema, subsystem_name);

	cookie = NULL;
	while ((name = nvlist_next(schema, &type, &cookie)) != NULL) {
		config = nvlist_get_nvlist(schema, name);

		if (dnvlist_get_bool(config, REQUIRED_SCHEMA_NAME, false)) {
			if (!nvlist_exists(subsystem, name))
				errx(1,
				    "Required parameter '%s' not found in '%s'",
				    name, config_name);
		}
	}
}