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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 int git_attr_get_many_with_session (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t,char const**) ; 

int git_attr_get_many(
	const char **values,
	git_repository *repo,
	uint32_t flags,
	const char *pathname,
	size_t num_attr,
	const char **names)
{
	return git_attr_get_many_with_session(
		values, repo, NULL, flags, pathname, num_attr, names);
}