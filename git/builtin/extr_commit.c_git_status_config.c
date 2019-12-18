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
struct wt_status {int submodule_summary; int rename_limit; int detect_rename; int /*<<< orphan*/  show_untracked_files; void* relative_paths; int /*<<< orphan*/ * color_palette; void* display_comment_prefix; int /*<<< orphan*/  use_color; void* show_stash; int /*<<< orphan*/  colopts; } ;
struct TYPE_2__ {void* ahead_behind; void* show_branch; int /*<<< orphan*/  status_format; } ;

/* Variables and functions */
 int /*<<< orphan*/  SHOW_ALL_UNTRACKED_FILES ; 
 int /*<<< orphan*/  SHOW_NORMAL_UNTRACKED_FILES ; 
 int /*<<< orphan*/  SHOW_NO_UNTRACKED_FILES ; 
 int /*<<< orphan*/  STATUS_FORMAT_NONE ; 
 int /*<<< orphan*/  STATUS_FORMAT_SHORT ; 
 int /*<<< orphan*/  _ (char*) ; 
 int color_parse (char const*,int /*<<< orphan*/ ) ; 
 int config_error_nonbool (char const*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 int git_column_config (char const*,char const*,char*,int /*<<< orphan*/ *) ; 
 void* git_config_bool (char const*,char const*) ; 
 int git_config_bool_or_int (char const*,char const*,int*) ; 
 int /*<<< orphan*/  git_config_colorbool (char const*,char const*) ; 
 void* git_config_int (char const*,char const*) ; 
 void* git_config_rename (char const*,char const*) ; 
 int git_diff_ui_config (char const*,char const*,int /*<<< orphan*/ *) ; 
 int parse_status_slot (char const*) ; 
 scalar_t__ skip_prefix (char const*,char*,char const**) ; 
 scalar_t__ starts_with (char const*,char*) ; 
 TYPE_1__ status_deferred_config ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int git_status_config(const char *k, const char *v, void *cb)
{
	struct wt_status *s = cb;
	const char *slot_name;

	if (starts_with(k, "column."))
		return git_column_config(k, v, "status", &s->colopts);
	if (!strcmp(k, "status.submodulesummary")) {
		int is_bool;
		s->submodule_summary = git_config_bool_or_int(k, v, &is_bool);
		if (is_bool && s->submodule_summary)
			s->submodule_summary = -1;
		return 0;
	}
	if (!strcmp(k, "status.short")) {
		if (git_config_bool(k, v))
			status_deferred_config.status_format = STATUS_FORMAT_SHORT;
		else
			status_deferred_config.status_format = STATUS_FORMAT_NONE;
		return 0;
	}
	if (!strcmp(k, "status.branch")) {
		status_deferred_config.show_branch = git_config_bool(k, v);
		return 0;
	}
	if (!strcmp(k, "status.aheadbehind")) {
		status_deferred_config.ahead_behind = git_config_bool(k, v);
		return 0;
	}
	if (!strcmp(k, "status.showstash")) {
		s->show_stash = git_config_bool(k, v);
		return 0;
	}
	if (!strcmp(k, "status.color") || !strcmp(k, "color.status")) {
		s->use_color = git_config_colorbool(k, v);
		return 0;
	}
	if (!strcmp(k, "status.displaycommentprefix")) {
		s->display_comment_prefix = git_config_bool(k, v);
		return 0;
	}
	if (skip_prefix(k, "status.color.", &slot_name) ||
	    skip_prefix(k, "color.status.", &slot_name)) {
		int slot = parse_status_slot(slot_name);
		if (slot < 0)
			return 0;
		if (!v)
			return config_error_nonbool(k);
		return color_parse(v, s->color_palette[slot]);
	}
	if (!strcmp(k, "status.relativepaths")) {
		s->relative_paths = git_config_bool(k, v);
		return 0;
	}
	if (!strcmp(k, "status.showuntrackedfiles")) {
		if (!v)
			return config_error_nonbool(k);
		else if (!strcmp(v, "no"))
			s->show_untracked_files = SHOW_NO_UNTRACKED_FILES;
		else if (!strcmp(v, "normal"))
			s->show_untracked_files = SHOW_NORMAL_UNTRACKED_FILES;
		else if (!strcmp(v, "all"))
			s->show_untracked_files = SHOW_ALL_UNTRACKED_FILES;
		else
			return error(_("Invalid untracked files mode '%s'"), v);
		return 0;
	}
	if (!strcmp(k, "diff.renamelimit")) {
		if (s->rename_limit == -1)
			s->rename_limit = git_config_int(k, v);
		return 0;
	}
	if (!strcmp(k, "status.renamelimit")) {
		s->rename_limit = git_config_int(k, v);
		return 0;
	}
	if (!strcmp(k, "diff.renames")) {
		if (s->detect_rename == -1)
			s->detect_rename = git_config_rename(k, v);
		return 0;
	}
	if (!strcmp(k, "status.renames")) {
		s->detect_rename = git_config_rename(k, v);
		return 0;
	}
	return git_diff_ui_config(k, v, NULL);
}