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
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*,char const*) ; 

__attribute__((used)) static int submodule_config_error(const char *property, const char *value)
{
	git_error_set(GIT_ERROR_INVALID,
		"invalid value for submodule '%s' property: '%s'", property, value);
	return -1;
}