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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 scalar_t__ git__parse_bool (int*,char const*) ; 
 scalar_t__ git_config_parse_int32 (int*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 

int git_config_parse_bool(int *out, const char *value)
{
	if (git__parse_bool(out, value) == 0)
		return 0;

	if (git_config_parse_int32(out, value) == 0) {
		*out = !!(*out);
		return 0;
	}

	git_error_set(GIT_ERROR_CONFIG, "failed to parse '%s' as a boolean value", value);
	return -1;
}