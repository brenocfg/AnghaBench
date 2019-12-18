#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ rebase_interactive_in_progress; } ;
struct wt_status {scalar_t__ hints; TYPE_1__ state; } ;
struct string_list {int nr; TYPE_2__* items; } ;
struct TYPE_4__ {int /*<<< orphan*/  string; } ;

/* Variables and functions */
 int /*<<< orphan*/  Q_ (char*,char*,int) ; 
 struct string_list STRING_LIST_INIT_DUP ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  git_path (char*) ; 
 scalar_t__ read_rebase_todolist (char*,struct string_list*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char const*,char*,...) ; 
 int /*<<< orphan*/  string_list_clear (struct string_list*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_rebase_information(struct wt_status *s,
				    const char *color)
{
	if (s->state.rebase_interactive_in_progress) {
		int i;
		int nr_lines_to_show = 2;

		struct string_list have_done = STRING_LIST_INIT_DUP;
		struct string_list yet_to_do = STRING_LIST_INIT_DUP;

		read_rebase_todolist("rebase-merge/done", &have_done);
		if (read_rebase_todolist("rebase-merge/git-rebase-todo",
					 &yet_to_do))
			status_printf_ln(s, color,
				_("git-rebase-todo is missing."));
		if (have_done.nr == 0)
			status_printf_ln(s, color, _("No commands done."));
		else {
			status_printf_ln(s, color,
				Q_("Last command done (%d command done):",
					"Last commands done (%d commands done):",
					have_done.nr),
				have_done.nr);
			for (i = (have_done.nr > nr_lines_to_show)
				? have_done.nr - nr_lines_to_show : 0;
				i < have_done.nr;
				i++)
				status_printf_ln(s, color, "   %s", have_done.items[i].string);
			if (have_done.nr > nr_lines_to_show && s->hints)
				status_printf_ln(s, color,
					_("  (see more in file %s)"), git_path("rebase-merge/done"));
		}

		if (yet_to_do.nr == 0)
			status_printf_ln(s, color,
					 _("No commands remaining."));
		else {
			status_printf_ln(s, color,
				Q_("Next command to do (%d remaining command):",
					"Next commands to do (%d remaining commands):",
					yet_to_do.nr),
				yet_to_do.nr);
			for (i = 0; i < nr_lines_to_show && i < yet_to_do.nr; i++)
				status_printf_ln(s, color, "   %s", yet_to_do.items[i].string);
			if (s->hints)
				status_printf_ln(s, color,
					_("  (use \"git rebase --edit-todo\" to view and edit)"));
		}
		string_list_clear(&yet_to_do, 0);
		string_list_clear(&have_done, 0);
	}
}