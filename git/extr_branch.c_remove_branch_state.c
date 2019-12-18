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

/* Variables and functions */
 int /*<<< orphan*/  git_path_squash_msg (struct repository*) ; 
 int /*<<< orphan*/  remove_merge_branch_state (struct repository*) ; 
 int /*<<< orphan*/  sequencer_post_commit_cleanup (struct repository*,int) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void remove_branch_state(struct repository *r, int verbose)
{
	sequencer_post_commit_cleanup(r, verbose);
	unlink(git_path_squash_msg(r));
	remove_merge_branch_state(r);
}