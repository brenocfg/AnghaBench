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
 int /*<<< orphan*/  RUN_GIT_CMD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  file_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_cherry_pick_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_revert_head (struct repository*) ; 
 int run_command_v_opt (char const**,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int continue_single_pick(struct repository *r)
{
	const char *argv[] = { "commit", NULL };

	if (!file_exists(git_path_cherry_pick_head(r)) &&
	    !file_exists(git_path_revert_head(r)))
		return error(_("no cherry-pick or revert in progress"));
	return run_command_v_opt(argv, RUN_GIT_CMD);
}