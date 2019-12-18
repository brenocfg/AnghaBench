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
struct repository {int dummy; } ;
struct replay_opts {int action; } ;
typedef  enum replay_action { ____Placeholder_replay_action } replay_action ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  REPLAY_PICK 129 
#define  REPLAY_REVERT 128 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ advice_resolve_conflict ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ,char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_revert_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_seq_dir () ; 
 int /*<<< orphan*/  is_directory (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rollback_is_safe () ; 
 int sequencer_continue (struct repository*,struct replay_opts*) ; 
 int /*<<< orphan*/  sequencer_get_last_command (struct repository*,int*) ; 
 scalar_t__ skip_single_pick () ; 

int sequencer_skip(struct repository *r, struct replay_opts *opts)
{
	enum replay_action action = -1;
	sequencer_get_last_command(r, &action);

	/*
	 * Check whether the subcommand requested to skip the commit is actually
	 * in progress and that it's safe to skip the commit.
	 *
	 * opts->action tells us which subcommand requested to skip the commit.
	 * If the corresponding .git/<ACTION>_HEAD exists, we know that the
	 * action is in progress and we can skip the commit.
	 *
	 * Otherwise we check that the last instruction was related to the
	 * particular subcommand we're trying to execute and barf if that's not
	 * the case.
	 *
	 * Finally we check that the rollback is "safe", i.e., has the HEAD
	 * moved? In this case, it doesn't make sense to "reset the merge" and
	 * "skip the commit" as the user already handled this by committing. But
	 * we'd not want to barf here, instead give advice on how to proceed. We
	 * only need to check that when .git/<ACTION>_HEAD doesn't exist because
	 * it gets removed when the user commits, so if it still exists we're
	 * sure the user can't have committed before.
	 */
	switch (opts->action) {
	case REPLAY_REVERT:
		if (!file_exists(git_path_revert_head(r))) {
			if (action != REPLAY_REVERT)
				return error(_("no revert in progress"));
			if (!rollback_is_safe())
				goto give_advice;
		}
		break;
	case REPLAY_PICK:
		if (!file_exists(git_path_cherry_pick_head(r))) {
			if (action != REPLAY_PICK)
				return error(_("no cherry-pick in progress"));
			if (!rollback_is_safe())
				goto give_advice;
		}
		break;
	default:
		BUG("unexpected action in sequencer_skip");
	}

	if (skip_single_pick())
		return error(_("failed to skip the commit"));
	if (!is_directory(git_path_seq_dir()))
		return 0;

	return sequencer_continue(r, opts);

give_advice:
	error(_("there is nothing to skip"));

	if (advice_resolve_conflict) {
		advise(_("have you committed already?\n"
			 "try \"git %s --continue\""),
			 action == REPLAY_REVERT ? "revert" : "cherry-pick");
	}
	return -1;
}