#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  size; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ ENOTDIR ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  futils__error_cannot_rmdir (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git__prefixcmp (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_buf_rtruncate_at_char (TYPE_1__*,char) ; 
 scalar_t__ p_lstat_posixly (int /*<<< orphan*/ ,struct stat*) ; 
 int p_unlink (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int futils__rm_first_parent(git_buf *path, const char *ceiling)
{
	int error = GIT_ENOTFOUND;
	struct stat st;

	while (error == GIT_ENOTFOUND) {
		git_buf_rtruncate_at_char(path, '/');

		if (!path->size || git__prefixcmp(path->ptr, ceiling) != 0)
			error = 0;
		else if (p_lstat_posixly(path->ptr, &st) == 0) {
			if (S_ISREG(st.st_mode) || S_ISLNK(st.st_mode))
				error = p_unlink(path->ptr);
			else if (!S_ISDIR(st.st_mode))
				error = -1; /* fail to remove non-regular file */
		} else if (errno != ENOTDIR)
			error = -1;
	}

	if (error)
		futils__error_cannot_rmdir(path->ptr, "cannot remove parent");

	return error;
}