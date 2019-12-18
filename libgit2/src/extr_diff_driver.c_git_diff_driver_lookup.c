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
typedef  int /*<<< orphan*/  git_diff_driver ;
typedef  int /*<<< orphan*/  git_attr_session ;

/* Variables and functions */
 size_t DIFF_DRIVER_AUTO ; 
 size_t DIFF_DRIVER_BINARY ; 
 size_t DIFF_DRIVER_TEXT ; 
 scalar_t__ GIT_ATTR_IS_FALSE (char const*) ; 
 scalar_t__ GIT_ATTR_IS_TRUE (char const*) ; 
 scalar_t__ GIT_ATTR_IS_UNSPECIFIED (char const*) ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ **) ; 
 int git_attr_get_many_with_session (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int,char const**) ; 
 int git_diff_driver_load (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/ * global_drivers ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_diff_driver_lookup(
	git_diff_driver **out, git_repository *repo,
	git_attr_session *attrsession, const char *path)
{
	int error = 0;
	const char *values[1], *attrs[] = { "diff" };

	assert(out);
	*out = NULL;

	if (!repo || !path || !strlen(path))
		/* just use the auto value */;
	else if ((error = git_attr_get_many_with_session(values, repo,
			attrsession, 0, path, 1, attrs)) < 0)
		/* return error below */;

	else if (GIT_ATTR_IS_UNSPECIFIED(values[0]))
		/* just use the auto value */;
	else if (GIT_ATTR_IS_FALSE(values[0]))
		*out = &global_drivers[DIFF_DRIVER_BINARY];
	else if (GIT_ATTR_IS_TRUE(values[0]))
		*out = &global_drivers[DIFF_DRIVER_TEXT];

	/* otherwise look for driver information in config and build driver */
	else if ((error = git_diff_driver_load(out, repo, values[0])) < 0) {
		if (error == GIT_ENOTFOUND) {
			error = 0;
			git_error_clear();
		}
	}

	if (!*out)
		*out = &global_drivers[DIFF_DRIVER_AUTO];

	return error;
}