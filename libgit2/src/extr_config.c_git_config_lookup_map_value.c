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
struct TYPE_3__ {int type; int map_value; int /*<<< orphan*/  str_match; } ;
typedef  TYPE_1__ git_configmap ;

/* Variables and functions */
#define  GIT_CONFIGMAP_FALSE 131 
#define  GIT_CONFIGMAP_INT32 130 
#define  GIT_CONFIGMAP_STRING 129 
#define  GIT_CONFIGMAP_TRUE 128 
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  git__parse_bool (int*,char const*) ; 
 int /*<<< orphan*/  git_config_parse_int32 (int*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  strcasecmp (char const*,int /*<<< orphan*/ ) ; 

int git_config_lookup_map_value(
	int *out,
	const git_configmap *maps,
	size_t map_n,
	const char *value)
{
	size_t i;

	if (!value)
		goto fail_parse;

	for (i = 0; i < map_n; ++i) {
		const git_configmap *m = maps + i;

		switch (m->type) {
		case GIT_CONFIGMAP_FALSE:
		case GIT_CONFIGMAP_TRUE: {
			int bool_val;

			if (git__parse_bool(&bool_val, value) == 0 &&
				bool_val == (int)m->type) {
				*out = m->map_value;
				return 0;
			}
			break;
		}

		case GIT_CONFIGMAP_INT32:
			if (git_config_parse_int32(out, value) == 0)
				return 0;
			break;

		case GIT_CONFIGMAP_STRING:
			if (strcasecmp(value, m->str_match) == 0) {
				*out = m->map_value;
				return 0;
			}
			break;
		}
	}

fail_parse:
	git_error_set(GIT_ERROR_CONFIG, "failed to map '%s'", value);
	return -1;
}