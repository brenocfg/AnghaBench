#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;
struct TYPE_11__ {int /*<<< orphan*/  st_mode; } ;
struct TYPE_13__ {int /*<<< orphan*/  path; TYPE_1__ st; } ;
typedef  TYPE_3__ filesystem_iterator_entry ;
struct TYPE_14__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_4__ filesystem_iterator ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int git_buf_joinpath (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iterator__descend_symlinks (TYPE_4__ const*) ; 
 int p_stat (int /*<<< orphan*/ ,struct stat*) ; 

__attribute__((used)) static int filesystem_iterator_is_dir(
	bool *is_dir,
	const filesystem_iterator *iter,
	const filesystem_iterator_entry *entry)
{
	struct stat st;
	git_buf fullpath = GIT_BUF_INIT;
	int error = 0;

	if (S_ISDIR(entry->st.st_mode)) {
		*is_dir = 1;
		goto done;
	}

	if (!iterator__descend_symlinks(iter) || !S_ISLNK(entry->st.st_mode)) {
		*is_dir = 0;
		goto done;
	}

	if ((error = git_buf_joinpath(&fullpath, iter->root, entry->path)) < 0 ||
		(error = p_stat(fullpath.ptr, &st)) < 0)
		goto done;

	*is_dir = S_ISDIR(st.st_mode);

done:
	git_buf_dispose(&fullpath);
	return error;
}