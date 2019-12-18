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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_7__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (TYPE_1__*) ; 
 int git_buf_sets (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int git_path_direach (TYPE_1__*,int /*<<< orphan*/ ,int (*) (void*,TYPE_1__*),void*) ; 
 int p_lstat_posixly (int /*<<< orphan*/ ,struct stat*) ; 
 int /*<<< orphan*/ * strstr (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int find_tmp_file_recurs(void *opaque, git_buf *path)
{
	int error = 0;
	git_buf *first_tmp_file = opaque;
	struct stat st;

	if ((error = p_lstat_posixly(path->ptr, &st)) < 0)
		return error;

	if (S_ISDIR(st.st_mode))
		return git_path_direach(path, 0, find_tmp_file_recurs, opaque);

	/* This is the template that's used in git_futils_mktmp. */
	if (strstr(git_buf_cstr(path), "_git2_") != NULL)
		return git_buf_sets(first_tmp_file, git_buf_cstr(path));

	return 0;
}