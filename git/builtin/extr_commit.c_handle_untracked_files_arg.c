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
struct wt_status {int /*<<< orphan*/  show_untracked_files; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHOW_ALL_UNTRACKED_FILES ; 
 int /*<<< orphan*/  SHOW_NORMAL_UNTRACKED_FILES ; 
 int /*<<< orphan*/  SHOW_NO_UNTRACKED_FILES ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  untracked_files_arg ; 

__attribute__((used)) static void handle_untracked_files_arg(struct wt_status *s)
{
	if (!untracked_files_arg)
		; /* default already initialized */
	else if (!strcmp(untracked_files_arg, "no"))
		s->show_untracked_files = SHOW_NO_UNTRACKED_FILES;
	else if (!strcmp(untracked_files_arg, "normal"))
		s->show_untracked_files = SHOW_NORMAL_UNTRACKED_FILES;
	else if (!strcmp(untracked_files_arg, "all"))
		s->show_untracked_files = SHOW_ALL_UNTRACKED_FILES;
	/*
	 * Please update $__git_untracked_file_modes in
	 * git-completion.bash when you add new options
	 */
	else
		die(_("Invalid untracked files mode '%s'"), untracked_files_arg);
}