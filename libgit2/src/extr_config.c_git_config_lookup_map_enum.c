#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_configmap_t ;
struct TYPE_3__ {int map_value; char* str_match; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ git_configmap ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 

int git_config_lookup_map_enum(git_configmap_t *type_out, const char **str_out,
			       const git_configmap *maps, size_t map_n, int enum_val)
{
	size_t i;

	for (i = 0; i < map_n; i++) {
		const git_configmap *m = &maps[i];

		if (m->map_value != enum_val)
			continue;

		*type_out = m->type;
		*str_out = m->str_match;
		return 0;
	}

	git_error_set(GIT_ERROR_CONFIG, "invalid enum value");
	return GIT_ENOTFOUND;
}