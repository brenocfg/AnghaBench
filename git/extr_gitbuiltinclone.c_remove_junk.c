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
struct strbuf {int dummy; } ;

/* Variables and functions */
#define  JUNK_LEAVE_ALL 129 
#define  JUNK_LEAVE_REPO 128 
 struct strbuf STRBUF_INIT ; 
 int /*<<< orphan*/  _ (int /*<<< orphan*/ ) ; 
 scalar_t__ junk_git_dir ; 
 int /*<<< orphan*/  junk_git_dir_flags ; 
 int /*<<< orphan*/  junk_leave_repo_msg ; 
 int junk_mode ; 
 scalar_t__ junk_work_tree ; 
 int /*<<< orphan*/  junk_work_tree_flags ; 
 int /*<<< orphan*/  remove_dir_recursively (struct strbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addstr (struct strbuf*,scalar_t__) ; 
 int /*<<< orphan*/  strbuf_release (struct strbuf*) ; 
 int /*<<< orphan*/  strbuf_reset (struct strbuf*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_junk(void)
{
	struct strbuf sb = STRBUF_INIT;

	switch (junk_mode) {
	case JUNK_LEAVE_REPO:
		warning("%s", _(junk_leave_repo_msg));
		/* fall-through */
	case JUNK_LEAVE_ALL:
		return;
	default:
		/* proceed to removal */
		break;
	}

	if (junk_git_dir) {
		strbuf_addstr(&sb, junk_git_dir);
		remove_dir_recursively(&sb, junk_git_dir_flags);
		strbuf_reset(&sb);
	}
	if (junk_work_tree) {
		strbuf_addstr(&sb, junk_work_tree);
		remove_dir_recursively(&sb, junk_work_tree_flags);
	}
	strbuf_release(&sb);
}