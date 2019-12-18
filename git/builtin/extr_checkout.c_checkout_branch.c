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
struct object_id {int dummy; } ;
struct TYPE_2__ {scalar_t__ nr; } ;
struct checkout_opts {int overlay_mode; scalar_t__ track; scalar_t__ new_branch; int /*<<< orphan*/  ignore_other_worktrees; scalar_t__ force_detach; int /*<<< orphan*/  can_switch_when_in_progress; int /*<<< orphan*/  new_branch_force; int /*<<< orphan*/  implicit_detach; int /*<<< orphan*/  switch_branch_doing_nothing_is_ok; scalar_t__ orphan_from_empty_tree; scalar_t__ new_orphan_branch; scalar_t__ merge; scalar_t__ discard_changes; scalar_t__ force; scalar_t__ writeout_stage; scalar_t__ patch_mode; TYPE_1__ pathspec; } ;
struct branch_info {int /*<<< orphan*/  commit; scalar_t__ path; scalar_t__ name; } ;

/* Variables and functions */
 scalar_t__ BRANCH_TRACK_UNSPECIFIED ; 
 int REF_ISSYMREF ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  die (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  die_expecting_a_branch (struct branch_info*) ; 
 int /*<<< orphan*/  die_if_checked_out (scalar_t__,int) ; 
 int /*<<< orphan*/  die_if_some_operation_in_progress () ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ git_branch_track ; 
 scalar_t__ is_null_oid (struct object_id*) ; 
 int /*<<< orphan*/  read_ref_full (char*,int /*<<< orphan*/ ,struct object_id*,int*) ; 
 char* resolve_refdup (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ strcmp (char*,scalar_t__) ; 
 int switch_branches (struct checkout_opts*,struct branch_info*) ; 
 int switch_unborn_to_new_branch (struct checkout_opts*) ; 

__attribute__((used)) static int checkout_branch(struct checkout_opts *opts,
			   struct branch_info *new_branch_info)
{
	if (opts->pathspec.nr)
		die(_("paths cannot be used with switching branches"));

	if (opts->patch_mode)
		die(_("'%s' cannot be used with switching branches"),
		    "--patch");

	if (opts->overlay_mode != -1)
		die(_("'%s' cannot be used with switching branches"),
		    "--[no]-overlay");

	if (opts->writeout_stage)
		die(_("'%s' cannot be used with switching branches"),
		    "--ours/--theirs");

	if (opts->force && opts->merge)
		die(_("'%s' cannot be used with '%s'"), "-f", "-m");

	if (opts->discard_changes && opts->merge)
		die(_("'%s' cannot be used with '%s'"), "--discard-changes", "--merge");

	if (opts->force_detach && opts->new_branch)
		die(_("'%s' cannot be used with '%s'"),
		    "--detach", "-b/-B/--orphan");

	if (opts->new_orphan_branch) {
		if (opts->track != BRANCH_TRACK_UNSPECIFIED)
			die(_("'%s' cannot be used with '%s'"), "--orphan", "-t");
		if (opts->orphan_from_empty_tree && new_branch_info->name)
			die(_("'%s' cannot take <start-point>"), "--orphan");
	} else if (opts->force_detach) {
		if (opts->track != BRANCH_TRACK_UNSPECIFIED)
			die(_("'%s' cannot be used with '%s'"), "--detach", "-t");
	} else if (opts->track == BRANCH_TRACK_UNSPECIFIED)
		opts->track = git_branch_track;

	if (new_branch_info->name && !new_branch_info->commit)
		die(_("Cannot switch branch to a non-commit '%s'"),
		    new_branch_info->name);

	if (!opts->switch_branch_doing_nothing_is_ok &&
	    !new_branch_info->name &&
	    !opts->new_branch &&
	    !opts->force_detach)
		die(_("missing branch or commit argument"));

	if (!opts->implicit_detach &&
	    !opts->force_detach &&
	    !opts->new_branch &&
	    !opts->new_branch_force &&
	    new_branch_info->name &&
	    !new_branch_info->path)
		die_expecting_a_branch(new_branch_info);

	if (!opts->can_switch_when_in_progress)
		die_if_some_operation_in_progress();

	if (new_branch_info->path && !opts->force_detach && !opts->new_branch &&
	    !opts->ignore_other_worktrees) {
		int flag;
		char *head_ref = resolve_refdup("HEAD", 0, NULL, &flag);
		if (head_ref &&
		    (!(flag & REF_ISSYMREF) || strcmp(head_ref, new_branch_info->path)))
			die_if_checked_out(new_branch_info->path, 1);
		free(head_ref);
	}

	if (!new_branch_info->commit && opts->new_branch) {
		struct object_id rev;
		int flag;

		if (!read_ref_full("HEAD", 0, &rev, &flag) &&
		    (flag & REF_ISSYMREF) && is_null_oid(&rev))
			return switch_unborn_to_new_branch(opts);
	}
	return switch_branches(opts, new_branch_info);
}