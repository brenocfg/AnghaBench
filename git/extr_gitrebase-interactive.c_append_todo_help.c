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
 scalar_t__ MISSING_COMMIT_CHECK_ERROR ; 
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 char* _ (char*) ; 
 scalar_t__ get_missing_commit_check_level () ; 
 int /*<<< orphan*/  strbuf_add_commented_lines (struct strbuf*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strbuf_addch (struct strbuf*,char) ; 
 int /*<<< orphan*/  strbuf_commented_addf (struct strbuf*,int /*<<< orphan*/ ,char const*,char const*,int) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void append_todo_help(unsigned keep_empty, int command_count,
		      const char *shortrevisions, const char *shortonto,
		      struct strbuf *buf)
{
	const char *msg = _("\nCommands:\n"
"p, pick <commit> = use commit\n"
"r, reword <commit> = use commit, but edit the commit message\n"
"e, edit <commit> = use commit, but stop for amending\n"
"s, squash <commit> = use commit, but meld into previous commit\n"
"f, fixup <commit> = like \"squash\", but discard this commit's log message\n"
"x, exec <command> = run command (the rest of the line) using shell\n"
"b, break = stop here (continue rebase later with 'git rebase --continue')\n"
"d, drop <commit> = remove commit\n"
"l, label <label> = label current HEAD with a name\n"
"t, reset <label> = reset HEAD to a label\n"
"m, merge [-C <commit> | -c <commit>] <label> [# <oneline>]\n"
".       create a merge commit using the original merge commit's\n"
".       message (or the oneline, if no original merge commit was\n"
".       specified). Use -c <commit> to reword the commit message.\n"
"\n"
"These lines can be re-ordered; they are executed from top to bottom.\n");
	unsigned edit_todo = !(shortrevisions && shortonto);

	if (!edit_todo) {
		strbuf_addch(buf, '\n');
		strbuf_commented_addf(buf, Q_("Rebase %s onto %s (%d command)",
					      "Rebase %s onto %s (%d commands)",
					      command_count),
				      shortrevisions, shortonto, command_count);
	}

	strbuf_add_commented_lines(buf, msg, strlen(msg));

	if (get_missing_commit_check_level() == MISSING_COMMIT_CHECK_ERROR)
		msg = _("\nDo not remove any line. Use 'drop' "
			 "explicitly to remove a commit.\n");
	else
		msg = _("\nIf you remove a line here "
			 "THAT COMMIT WILL BE LOST.\n");

	strbuf_add_commented_lines(buf, msg, strlen(msg));

	if (edit_todo)
		msg = _("\nYou are editing the todo file "
			"of an ongoing interactive rebase.\n"
			"To continue rebase after editing, run:\n"
			"    git rebase --continue\n\n");
	else
		msg = _("\nHowever, if you remove everything, "
			"the rebase will be aborted.\n\n");

	strbuf_add_commented_lines(buf, msg, strlen(msg));

	if (!keep_empty) {
		msg = _("Note that empty commits are commented out");
		strbuf_add_commented_lines(buf, msg, strlen(msg));
	}
}