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
typedef  enum replay_action { ____Placeholder_replay_action } replay_action ;

/* Variables and functions */
 int /*<<< orphan*/  BUG (char*) ; 
#define  REPLAY_PICK 129 
#define  REPLAY_REVERT 128 
 char* _ (char*) ; 
 scalar_t__ advice_sequencer_in_use ; 
 int /*<<< orphan*/  advise (char const*,char*) ; 
 int /*<<< orphan*/  error (char*,char const*) ; 
 int error_errno (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_revert_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_seq_dir () ; 
 scalar_t__ mkdir (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sequencer_get_last_command (struct repository*,int*) ; 

__attribute__((used)) static int create_seq_dir(struct repository *r)
{
	enum replay_action action;
	const char *in_progress_error = NULL;
	const char *in_progress_advice = NULL;
	unsigned int advise_skip = file_exists(git_path_revert_head(r)) ||
				file_exists(git_path_cherry_pick_head(r));

	if (!sequencer_get_last_command(r, &action)) {
		switch (action) {
		case REPLAY_REVERT:
			in_progress_error = _("revert is already in progress");
			in_progress_advice =
			_("try \"git revert (--continue | %s--abort | --quit)\"");
			break;
		case REPLAY_PICK:
			in_progress_error = _("cherry-pick is already in progress");
			in_progress_advice =
			_("try \"git cherry-pick (--continue | %s--abort | --quit)\"");
			break;
		default:
			BUG("unexpected action in create_seq_dir");
		}
	}
	if (in_progress_error) {
		error("%s", in_progress_error);
		if (advice_sequencer_in_use)
			advise(in_progress_advice,
				advise_skip ? "--skip | " : "");
		return -1;
	}
	if (mkdir(git_path_seq_dir(), 0777) < 0)
		return error_errno(_("could not create sequencer directory '%s'"),
				   git_path_seq_dir());

	return 0;
}