#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int ignore_submodules; int override_submodule_config; int quick; } ;
struct TYPE_5__ {TYPE_1__ flags; } ;
struct rev_info {TYPE_2__ diffopt; } ;
struct repository {int dummy; } ;

/* Variables and functions */
 int diff_result_code (TYPE_2__*,int) ; 
 int /*<<< orphan*/  diff_setup_done (TYPE_2__*) ; 
 int /*<<< orphan*/  repo_init_revisions (struct repository*,struct rev_info*,int /*<<< orphan*/ *) ; 
 int run_diff_files (struct rev_info*,int /*<<< orphan*/ ) ; 

int has_unstaged_changes(struct repository *r, int ignore_submodules)
{
	struct rev_info rev_info;
	int result;

	repo_init_revisions(r, &rev_info, NULL);
	if (ignore_submodules) {
		rev_info.diffopt.flags.ignore_submodules = 1;
		rev_info.diffopt.flags.override_submodule_config = 1;
	}
	rev_info.diffopt.flags.quick = 1;
	diff_setup_done(&rev_info.diffopt);
	result = run_diff_files(&rev_info, 0);
	return diff_result_code(&rev_info.diffopt, result);
}