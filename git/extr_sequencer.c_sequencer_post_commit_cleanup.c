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
struct replay_opts {int /*<<< orphan*/  action; } ;

/* Variables and functions */
 struct replay_opts REPLAY_OPTS_INIT ; 
 int /*<<< orphan*/  REPLAY_PICK ; 
 int /*<<< orphan*/  REPLAY_REVERT ; 
 int /*<<< orphan*/  _ (char*) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_revert_head (struct repository*) ; 
 int /*<<< orphan*/  have_finished_the_last_pick () ; 
 int /*<<< orphan*/  sequencer_remove_state (struct replay_opts*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ) ; 

void sequencer_post_commit_cleanup(struct repository *r, int verbose)
{
	struct replay_opts opts = REPLAY_OPTS_INIT;
	int need_cleanup = 0;

	if (file_exists(git_path_cherry_pick_head(r))) {
		if (!unlink(git_path_cherry_pick_head(r)) && verbose)
			warning(_("cancelling a cherry picking in progress"));
		opts.action = REPLAY_PICK;
		need_cleanup = 1;
	}

	if (file_exists(git_path_revert_head(r))) {
		if (!unlink(git_path_revert_head(r)) && verbose)
			warning(_("cancelling a revert in progress"));
		opts.action = REPLAY_REVERT;
		need_cleanup = 1;
	}

	if (!need_cleanup)
		return;

	if (!have_finished_the_last_pick())
		return;

	sequencer_remove_state(&opts);
}