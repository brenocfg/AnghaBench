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
 char* action_name (struct replay_opts*) ; 
 scalar_t__ advice_commit_before_merge ; 
 int /*<<< orphan*/  advise (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int error_resolve_conflict (int /*<<< orphan*/ ) ; 
 scalar_t__ repo_read_index_unmerged (struct repository*) ; 

__attribute__((used)) static int error_dirty_index(struct repository *repo, struct replay_opts *opts)
{
	if (repo_read_index_unmerged(repo))
		return error_resolve_conflict(_(action_name(opts)));

	error(_("your local changes would be overwritten by %s."),
		_(action_name(opts)));

	if (advice_commit_before_merge)
		advise(_("commit your changes or stash them to proceed."));
	return -1;
}