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

/* Variables and functions */
 scalar_t__ GIT_ATTR_IS_FALSE (char const*) ; 
 scalar_t__ GIT_ATTR_IS_TRUE (char const*) ; 
 scalar_t__ GIT_ATTR_IS_UNSPECIFIED (char const*) ; 
 int git_attr_get (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*) ; 
 char* merge_driver_name__binary ; 
 char* merge_driver_name__text ; 

__attribute__((used)) static int merge_driver_name_for_path(
	const char **out,
	git_repository *repo,
	const char *path,
	const char *default_driver)
{
	const char *value;
	int error;

	*out = NULL;

	if ((error = git_attr_get(&value, repo, 0, path, "merge")) < 0)
		return error;

	/* set: use the built-in 3-way merge driver ("text") */
	if (GIT_ATTR_IS_TRUE(value))
		*out = merge_driver_name__text;

	/* unset: do not merge ("binary") */
	else if (GIT_ATTR_IS_FALSE(value))
		*out = merge_driver_name__binary;

	else if (GIT_ATTR_IS_UNSPECIFIED(value) && default_driver)
		*out = default_driver;

	else if (GIT_ATTR_IS_UNSPECIFIED(value))
		*out = merge_driver_name__text;

	else
		*out = value;

	return 0;
}