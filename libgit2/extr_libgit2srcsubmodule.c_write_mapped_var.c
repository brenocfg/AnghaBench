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
typedef  int /*<<< orphan*/  git_repository ;
typedef  scalar_t__ git_cvar_t ;
typedef  int /*<<< orphan*/  git_cvar_map ;

/* Variables and functions */
 scalar_t__ GIT_CVAR_TRUE ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 scalar_t__ git_config_lookup_map_enum (scalar_t__*,char const**,int /*<<< orphan*/ *,size_t,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int write_var (int /*<<< orphan*/ *,char const*,char const*,char const*) ; 

__attribute__((used)) static int write_mapped_var(git_repository *repo, const char *name, git_cvar_map *maps, size_t nmaps, const char *var, int ival)
{
	git_cvar_t type;
	const char *val;

	if (git_config_lookup_map_enum(&type, &val, maps, nmaps, ival) < 0) {
		git_error_set(GIT_ERROR_SUBMODULE, "invalid value for %s", var);
		return -1;
	}

	if (type == GIT_CVAR_TRUE)
		val = "true";

	return write_var(repo, name, var, val);
}