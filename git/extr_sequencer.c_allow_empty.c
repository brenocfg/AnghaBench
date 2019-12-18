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
struct replay_opts {scalar_t__ keep_redundant_commits; int /*<<< orphan*/  allow_empty; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int is_index_unchanged (struct repository*) ; 
 int is_original_commit_empty (struct commit*) ; 

__attribute__((used)) static int allow_empty(struct repository *r,
		       struct replay_opts *opts,
		       struct commit *commit)
{
	int index_unchanged, empty_commit;

	/*
	 * Three cases:
	 *
	 * (1) we do not allow empty at all and error out.
	 *
	 * (2) we allow ones that were initially empty, but
	 * forbid the ones that become empty;
	 *
	 * (3) we allow both.
	 */
	if (!opts->allow_empty)
		return 0; /* let "git commit" barf as necessary */

	index_unchanged = is_index_unchanged(r);
	if (index_unchanged < 0)
		return index_unchanged;
	if (!index_unchanged)
		return 0; /* we do not have to say --allow-empty */

	if (opts->keep_redundant_commits)
		return 1;

	empty_commit = is_original_commit_empty(commit);
	if (empty_commit < 0)
		return empty_commit;
	if (!empty_commit)
		return 0;
	else
		return 1;
}