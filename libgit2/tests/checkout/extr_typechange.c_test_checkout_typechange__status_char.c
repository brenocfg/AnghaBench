#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_6__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
struct TYPE_7__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_DIFF_INCLUDE_TYPECHANGE ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff__commit (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_find_similar (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 TYPE_2__* git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_status_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 

void test_checkout_typechange__status_char(void)
{
	size_t i;
	git_oid oid;
	git_commit *commit;
	git_diff *diff;
	const git_diff_delta *delta;
	git_diff_options diffopts = GIT_DIFF_OPTIONS_INIT;
	char expected[8] = {'M', 'M', 'R', 'T', 'D', 'R', 'A', 'R'};

	git_oid_fromstr(&oid, "9b19edf33a03a0c59cdfc113bfa5c06179bf9b1a");
	cl_git_pass(git_commit_lookup(&commit, g_repo, &oid));
	diffopts.flags |= GIT_DIFF_INCLUDE_TYPECHANGE;
	cl_git_pass(git_diff__commit(&diff, g_repo, commit, &diffopts));
	cl_git_pass(git_diff_find_similar(diff, NULL));

	for (i = 0; i < git_diff_num_deltas(diff); i++) {
		delta = git_diff_get_delta(diff, i);
		cl_assert_equal_i(expected[i], git_diff_status_char(delta->status));
	}

	git_diff_free(diff);
	git_commit_free(commit);
}