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
typedef  scalar_t__ git_submodule_ignore_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ GIT_SUBMODULE_IGNORE_NONE ; 
 int /*<<< orphan*/  _sm_ignore_map ; 
 scalar_t__ git_config_lookup_map_value (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int submodule_config_error (char*,char const*) ; 

int git_submodule_parse_ignore(git_submodule_ignore_t *out, const char *value)
{
	int val;

	if (git_config_lookup_map_value(
			&val, _sm_ignore_map, ARRAY_SIZE(_sm_ignore_map), value) < 0) {
		*out = GIT_SUBMODULE_IGNORE_NONE;
		return submodule_config_error("ignore", value);
	}

	*out = (git_submodule_ignore_t)val;
	return 0;
}