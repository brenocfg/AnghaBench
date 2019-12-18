#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_5__ {int flags; TYPE_2__* payload; int /*<<< orphan*/  notify_cb; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_6__ {char* member_0; int /*<<< orphan*/  member_1; } ;
typedef  TYPE_2__ basic_payload ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DELTA_IGNORED ; 
 int /*<<< orphan*/  GIT_DELTA_MODIFIED ; 
 int GIT_DIFF_INCLUDE_IGNORED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int GIT_DIFF_RECURSE_UNTRACKED_DIRS ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  notify_cb__basic ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_diff_racediffiter__basic(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_repository *repo = cl_git_sandbox_init("diff");
	git_diff *diff;

	basic_payload exp_a[] = {
		{ "another.txt", GIT_DELTA_MODIFIED },
		{ "readme.txt", GIT_DELTA_MODIFIED },
		{ "zzzzz/", GIT_DELTA_IGNORED },
		{ NULL, 0 }
	};

	cl_must_pass(p_mkdir("diff/zzzzz", 0777));

	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_RECURSE_UNTRACKED_DIRS;
	opts.notify_cb = notify_cb__basic;
	opts.payload = exp_a;

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, &opts));

	git_diff_free(diff);
}