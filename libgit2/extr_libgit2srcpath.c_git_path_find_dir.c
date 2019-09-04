#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int GIT_PATH_MAX ; 
 int git_buf_sets (TYPE_1__*,char*) ; 
 scalar_t__ git_path_dirname_r (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_path_join_unrooted (TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int git_path_to_dir (TYPE_1__*) ; 
 int /*<<< orphan*/ * p_realpath (int /*<<< orphan*/ ,char*) ; 

int git_path_find_dir(git_buf *dir, const char *path, const char *base)
{
	int error = git_path_join_unrooted(dir, path, base, NULL);

	if (!error) {
		char buf[GIT_PATH_MAX];
		if (p_realpath(dir->ptr, buf) != NULL)
			error = git_buf_sets(dir, buf);
	}

	/* call dirname if this is not a directory */
	if (!error) /* && git_path_isdir(dir->ptr) == false) */
		error = (git_path_dirname_r(dir, dir->ptr) < 0) ? -1 : 0;

	if (!error)
		error = git_path_to_dir(dir);

	return error;
}