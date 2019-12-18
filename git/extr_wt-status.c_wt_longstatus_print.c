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
struct TYPE_4__ {scalar_t__ nr; } ;
struct TYPE_3__ {char* onto; char* detached_from; scalar_t__ detached_at; scalar_t__ rebase_interactive_in_progress; scalar_t__ rebase_in_progress; } ;
struct wt_status {char* branch; char const* ignore_submodule_arg; int untracked_in_ms; scalar_t__ show_stash; scalar_t__ hints; scalar_t__ show_untracked_files; scalar_t__ is_initial; TYPE_2__ untracked; scalar_t__ workdir_dirty; scalar_t__ nowarn; scalar_t__ amend; scalar_t__ committable; scalar_t__ verbose; TYPE_2__ ignored; scalar_t__ show_ignored_mode; scalar_t__ submodule_summary; scalar_t__ commit_template; TYPE_1__ state; } ;

/* Variables and functions */
 char* GIT_COLOR_NORMAL ; 
 char* HEAD_DETACHED_AT ; 
 char* HEAD_DETACHED_FROM ; 
 int /*<<< orphan*/  WT_STATUS_HEADER ; 
 int /*<<< orphan*/  WT_STATUS_NOBRANCH ; 
 int /*<<< orphan*/  WT_STATUS_ONBRANCH ; 
 char* _ (char*) ; 
 scalar_t__ advice_status_u_option ; 
 char* color (int /*<<< orphan*/ ,struct wt_status*) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  skip_prefix (char const*,char*,char const**) ; 
 int /*<<< orphan*/  status_printf (struct wt_status*,char*,char*,char*) ; 
 int /*<<< orphan*/  status_printf_ln (struct wt_status*,char*,char*,...) ; 
 int /*<<< orphan*/  status_printf_more (struct wt_status*,char const*,char*,char const*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  wt_longstatus_print_changed (struct wt_status*) ; 
 int /*<<< orphan*/  wt_longstatus_print_other (struct wt_status*,TYPE_2__*,char*,char*) ; 
 int /*<<< orphan*/  wt_longstatus_print_stash_summary (struct wt_status*) ; 
 int /*<<< orphan*/  wt_longstatus_print_state (struct wt_status*) ; 
 int /*<<< orphan*/  wt_longstatus_print_submodule_summary (struct wt_status*,int) ; 
 int /*<<< orphan*/  wt_longstatus_print_tracking (struct wt_status*) ; 
 int /*<<< orphan*/  wt_longstatus_print_unmerged (struct wt_status*) ; 
 int /*<<< orphan*/  wt_longstatus_print_updated (struct wt_status*) ; 
 int /*<<< orphan*/  wt_longstatus_print_verbose (struct wt_status*) ; 

__attribute__((used)) static void wt_longstatus_print(struct wt_status *s)
{
	const char *branch_color = color(WT_STATUS_ONBRANCH, s);
	const char *branch_status_color = color(WT_STATUS_HEADER, s);

	if (s->branch) {
		const char *on_what = _("On branch ");
		const char *branch_name = s->branch;
		if (!strcmp(branch_name, "HEAD")) {
			branch_status_color = color(WT_STATUS_NOBRANCH, s);
			if (s->state.rebase_in_progress ||
			    s->state.rebase_interactive_in_progress) {
				if (s->state.rebase_interactive_in_progress)
					on_what = _("interactive rebase in progress; onto ");
				else
					on_what = _("rebase in progress; onto ");
				branch_name = s->state.onto;
			} else if (s->state.detached_from) {
				branch_name = s->state.detached_from;
				if (s->state.detached_at)
					on_what = HEAD_DETACHED_AT;
				else
					on_what = HEAD_DETACHED_FROM;
			} else {
				branch_name = "";
				on_what = _("Not currently on any branch.");
			}
		} else
			skip_prefix(branch_name, "refs/heads/", &branch_name);
		status_printf(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_more(s, branch_status_color, "%s", on_what);
		status_printf_more(s, branch_color, "%s\n", branch_name);
		if (!s->is_initial)
			wt_longstatus_print_tracking(s);
	}

	wt_longstatus_print_state(s);

	if (s->is_initial) {
		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
		status_printf_ln(s, color(WT_STATUS_HEADER, s),
				 s->commit_template
				 ? _("Initial commit")
				 : _("No commits yet"));
		status_printf_ln(s, color(WT_STATUS_HEADER, s), "%s", "");
	}

	wt_longstatus_print_updated(s);
	wt_longstatus_print_unmerged(s);
	wt_longstatus_print_changed(s);
	if (s->submodule_summary &&
	    (!s->ignore_submodule_arg ||
	     strcmp(s->ignore_submodule_arg, "all"))) {
		wt_longstatus_print_submodule_summary(s, 0);  /* staged */
		wt_longstatus_print_submodule_summary(s, 1);  /* unstaged */
	}
	if (s->show_untracked_files) {
		wt_longstatus_print_other(s, &s->untracked, _("Untracked files"), "add");
		if (s->show_ignored_mode)
			wt_longstatus_print_other(s, &s->ignored, _("Ignored files"), "add -f");
		if (advice_status_u_option && 2000 < s->untracked_in_ms) {
			status_printf_ln(s, GIT_COLOR_NORMAL, "%s", "");
			status_printf_ln(s, GIT_COLOR_NORMAL,
					 _("It took %.2f seconds to enumerate untracked files. 'status -uno'\n"
					   "may speed it up, but you have to be careful not to forget to add\n"
					   "new files yourself (see 'git help status')."),
					 s->untracked_in_ms / 1000.0);
		}
	} else if (s->committable)
		status_printf_ln(s, GIT_COLOR_NORMAL, _("Untracked files not listed%s"),
			s->hints
			? _(" (use -u option to show untracked files)") : "");

	if (s->verbose)
		wt_longstatus_print_verbose(s);
	if (!s->committable) {
		if (s->amend)
			status_printf_ln(s, GIT_COLOR_NORMAL, _("No changes"));
		else if (s->nowarn)
			; /* nothing */
		else if (s->workdir_dirty) {
			if (s->hints)
				printf(_("no changes added to commit "
					 "(use \"git add\" and/or \"git commit -a\")\n"));
			else
				printf(_("no changes added to commit\n"));
		} else if (s->untracked.nr) {
			if (s->hints)
				printf(_("nothing added to commit but untracked files "
					 "present (use \"git add\" to track)\n"));
			else
				printf(_("nothing added to commit but untracked files present\n"));
		} else if (s->is_initial) {
			if (s->hints)
				printf(_("nothing to commit (create/copy files "
					 "and use \"git add\" to track)\n"));
			else
				printf(_("nothing to commit\n"));
		} else if (!s->show_untracked_files) {
			if (s->hints)
				printf(_("nothing to commit (use -u to show untracked files)\n"));
			else
				printf(_("nothing to commit\n"));
		} else
			printf(_("nothing to commit, working tree clean\n"));
	}
	if(s->show_stash)
		wt_longstatus_print_stash_summary(s);
}