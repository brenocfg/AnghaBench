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
struct worktree {int dummy; } ;
struct strbuf {int /*<<< orphan*/  buf; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_ARRAY (struct worktree**,int) ; 
 int /*<<< orphan*/  ALLOC_GROW (struct worktree**,int,int) ; 
 unsigned int GWT_SORT_LINKED ; 
 int /*<<< orphan*/  QSORT (struct worktree**,int,int /*<<< orphan*/ ) ; 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compare_worktree ; 
 int /*<<< orphan*/  get_git_common_dir () ; 
 struct worktree* get_linked_worktree (int /*<<< orphan*/ ) ; 
 struct worktree* get_main_worktree () ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mark_current_worktree (struct worktree**) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strbuf_addf (struct strbuf*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 

struct worktree **get_worktrees(unsigned flags)
{
	struct worktree **list = NULL;
	struct strbuf path = STRBUF_INIT;
	DIR *dir;
	struct dirent *d;
	int counter = 0, alloc = 2;

	ALLOC_ARRAY(list, alloc);

	list[counter++] = get_main_worktree();

	strbuf_addf(&path, "%s/worktrees", get_git_common_dir());
	dir = opendir(path.buf);
	strbuf_release(&path);
	if (dir) {
		while ((d = readdir(dir)) != NULL) {
			struct worktree *linked = NULL;
			if (is_dot_or_dotdot(d->d_name))
				continue;

			if ((linked = get_linked_worktree(d->d_name))) {
				ALLOC_GROW(list, counter + 1, alloc);
				list[counter++] = linked;
			}
		}
		closedir(dir);
	}
	ALLOC_GROW(list, counter + 1, alloc);
	list[counter] = NULL;

	if (flags & GWT_SORT_LINKED)
		/*
		 * don't sort the first item (main worktree), which will
		 * always be the first
		 */
		QSORT(list + 1, counter - 1, compare_worktree);

	mark_current_worktree(list);
	return list;
}