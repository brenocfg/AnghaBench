#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  char const git_repository ;
struct TYPE_3__ {int /*<<< orphan*/  target_directory; } ;
struct TYPE_4__ {TYPE_1__ opts; } ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_RMDIR_EMPTY_PARENTS ; 
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* data ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int git_futils_rmdir_r (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int checkout_deferred_remove(git_repository *repo, const char *path)
{
#if 0
	int error = git_futils_rmdir_r(
		path, data->opts.target_directory, GIT_RMDIR_EMPTY_PARENTS);

	if (error == GIT_ENOTFOUND) {
		error = 0;
		git_error_clear();
	}

	return error;
#else
	GIT_UNUSED(repo);
	GIT_UNUSED(path);
	assert(false);
	return 0;
#endif
}