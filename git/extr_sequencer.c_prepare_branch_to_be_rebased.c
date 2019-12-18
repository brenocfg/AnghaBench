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
struct replay_opts {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ,char const*) ; 
 char* reflog_message (struct replay_opts*,char*,char*,char const*) ; 
 scalar_t__ run_git_checkout (struct repository*,struct replay_opts*,char const*,char const*) ; 

int prepare_branch_to_be_rebased(struct repository *r, struct replay_opts *opts,
				 const char *commit)
{
	const char *action;

	if (commit && *commit) {
		action = reflog_message(opts, "start", "checkout %s", commit);
		if (run_git_checkout(r, opts, commit, action))
			return error(_("could not checkout %s"), commit);
	}

	return 0;
}