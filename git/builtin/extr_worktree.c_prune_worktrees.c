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
struct strbuf {char* buf; } ;
struct dirent {int /*<<< orphan*/  d_name; } ;
typedef  int /*<<< orphan*/  DIR ;

/* Variables and functions */
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  closedir (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delete_git_dir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delete_worktrees_dir_if_empty () ; 
 int /*<<< orphan*/  git_path (char*) ; 
 scalar_t__ is_dot_or_dotdot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opendir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  prune_worktree (int /*<<< orphan*/ ,struct strbuf*) ; 
 struct dirent* readdir (int /*<<< orphan*/ *) ; 
 scalar_t__ show_only ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void prune_worktrees(void)
{
	struct strbuf reason = STRBUF_INIT;
	DIR *dir = opendir(git_path("worktrees"));
	struct dirent *d;
	if (!dir)
		return;
	while ((d = readdir(dir)) != NULL) {
		if (is_dot_or_dotdot(d->d_name))
			continue;
		strbuf_reset(&reason);
		if (!prune_worktree(d->d_name, &reason))
			continue;
		if (show_only || verbose)
			printf("%s\n", reason.buf);
		if (show_only)
			continue;
		delete_git_dir(d->d_name);
	}
	closedir(dir);
	if (!show_only)
		delete_worktrees_dir_if_empty();
	strbuf_release(&reason);
}