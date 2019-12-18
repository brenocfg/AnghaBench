#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  git_buf ;
struct TYPE_5__ {char const* base; int flags; int /*<<< orphan*/  baselen; } ;
typedef  TYPE_1__ futils__rmdir_data ;
typedef  int /*<<< orphan*/  data ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int GIT_ITEROVER ; 
 int GIT_RMDIR_EMPTY_PARENTS ; 
 int /*<<< orphan*/  futils__rmdir_empty_parent ; 
 int futils__rmdir_recurs_foreach (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 scalar_t__ git_path_join_unrooted (int /*<<< orphan*/ *,char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_path_walk_up (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

int git_futils_rmdir_r(
	const char *path, const char *base, uint32_t flags)
{
	int error;
	git_buf fullpath = GIT_BUF_INIT;
	futils__rmdir_data data;

	/* build path and find "root" where we should start calling mkdir */
	if (git_path_join_unrooted(&fullpath, path, base, NULL) < 0)
		return -1;

	memset(&data, 0, sizeof(data));
	data.base    = base ? base : "";
	data.baselen = base ? strlen(base) : 0;
	data.flags   = flags;

	error = futils__rmdir_recurs_foreach(&data, &fullpath);

	/* remove now-empty parents if requested */
	if (!error && (flags & GIT_RMDIR_EMPTY_PARENTS) != 0)
		error = git_path_walk_up(
			&fullpath, base, futils__rmdir_empty_parent, &data);

	if (error == GIT_ITEROVER) {
		git_error_clear();
		error = 0;
	}

	git_buf_dispose(&fullpath);

	return error;
}