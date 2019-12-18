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
 int /*<<< orphan*/  git_path_merge_head (struct repository*) ; 
 int /*<<< orphan*/  git_path_merge_mode (struct repository*) ; 
 int /*<<< orphan*/  git_path_merge_msg (struct repository*) ; 
 int /*<<< orphan*/  git_path_merge_rr (struct repository*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void remove_merge_branch_state(struct repository *r)
{
	unlink(git_path_merge_head(r));
	unlink(git_path_merge_rr(r));
	unlink(git_path_merge_msg(r));
	unlink(git_path_merge_mode(r));
}