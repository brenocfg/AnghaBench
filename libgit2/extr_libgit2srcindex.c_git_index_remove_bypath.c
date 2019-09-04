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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_index_remove (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int index_conflict_to_reuc (int /*<<< orphan*/ *,char const*) ; 

int git_index_remove_bypath(git_index *index, const char *path)
{
	int ret;

	assert(index && path);

	if (((ret = git_index_remove(index, path, 0)) < 0 &&
		ret != GIT_ENOTFOUND) ||
		((ret = index_conflict_to_reuc(index, path)) < 0 &&
		ret != GIT_ENOTFOUND))
		return ret;

	if (ret == GIT_ENOTFOUND)
		git_error_clear();

	return 0;
}