#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct apply_state {scalar_t__ cached; TYPE_1__* repo; scalar_t__ check_index; } ;
struct TYPE_2__ {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int EXISTS_IN_INDEX ; 
 int EXISTS_IN_WORKTREE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int error_errno (char*,char const*) ; 
 scalar_t__ has_symlink_leading_path (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ index_name_pos (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_missing_file_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstat (char const*,struct stat*) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int check_to_create(struct apply_state *state,
			   const char *new_name,
			   int ok_if_exists)
{
	struct stat nst;

	if (state->check_index &&
	    index_name_pos(state->repo->index, new_name, strlen(new_name)) >= 0 &&
	    !ok_if_exists)
		return EXISTS_IN_INDEX;
	if (state->cached)
		return 0;

	if (!lstat(new_name, &nst)) {
		if (S_ISDIR(nst.st_mode) || ok_if_exists)
			return 0;
		/*
		 * A leading component of new_name might be a symlink
		 * that is going to be removed with this patch, but
		 * still pointing at somewhere that has the path.
		 * In such a case, path "new_name" does not exist as
		 * far as git is concerned.
		 */
		if (has_symlink_leading_path(new_name, strlen(new_name)))
			return 0;

		return EXISTS_IN_WORKTREE;
	} else if (!is_missing_file_error(errno)) {
		return error_errno("%s", new_name);
	}
	return 0;
}