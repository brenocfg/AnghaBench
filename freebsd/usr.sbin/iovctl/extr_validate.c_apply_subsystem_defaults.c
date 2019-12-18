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
#define  NV_TYPE_BINARY 132 
#define  NV_TYPE_BOOL 131 
#define  NV_TYPE_NUMBER 130 
#define  NV_TYPE_NVLIST 129 
#define  NV_TYPE_STRING 128 
 int /*<<< orphan*/  errx (int,char*,int) ; 
 int /*<<< orphan*/  nvlist_add_binary (int /*<<< orphan*/ *,char const*,void const*,size_t) ; 
 int /*<<< orphan*/  nvlist_add_bool (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_number (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ nvlist_exists (int /*<<< orphan*/ *,char const*) ; 
 void* nvlist_get_binary (int /*<<< orphan*/  const*,char const*,size_t*) ; 
 int /*<<< orphan*/  nvlist_get_bool (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  nvlist_get_number (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/ * nvlist_get_nvlist (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  nvlist_get_string (int /*<<< orphan*/  const*,char const*) ; 
 int /*<<< orphan*/  nvlist_move_nvlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 char* nvlist_next (int /*<<< orphan*/  const*,int*,void**) ; 
 int /*<<< orphan*/ * nvlist_take_nvlist (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static void
apply_subsystem_defaults(nvlist_t *device_config, const char *subsystem,
    const nvlist_t *device_defaults)
{
	nvlist_t *config;
	const nvlist_t *defaults;
	const char *name;
	void *cookie;
	size_t len;
	const void *bin;
	int type;

	config = nvlist_take_nvlist(device_config, subsystem);
	defaults = nvlist_get_nvlist(device_defaults, subsystem);

	cookie = NULL;
	while ((name = nvlist_next(defaults, &type, &cookie)) != NULL) {
		if (nvlist_exists(config, name))
			continue;

		switch (type) {
		case NV_TYPE_BOOL:
			nvlist_add_bool(config, name,
			    nvlist_get_bool(defaults, name));
			break;
		case NV_TYPE_NUMBER:
			nvlist_add_number(config, name,
			    nvlist_get_number(defaults, name));
			break;
		case NV_TYPE_STRING:
			nvlist_add_string(config, name,
			    nvlist_get_string(defaults, name));
			break;
		case NV_TYPE_NVLIST:
			nvlist_add_nvlist(config, name,
			    nvlist_get_nvlist(defaults, name));
			break;
		case NV_TYPE_BINARY:
			bin = nvlist_get_binary(defaults, name, &len);
			nvlist_add_binary(config, name, bin, len);
			break;
		default:
			errx(1, "Unexpected type '%d'", type);
		}
	}
	nvlist_move_nvlist(device_config, subsystem, config);
}