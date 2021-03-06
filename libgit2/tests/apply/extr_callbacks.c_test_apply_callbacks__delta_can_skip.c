#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  workdir_expected ;
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_4__ {int /*<<< orphan*/  delta_cb; } ;
typedef  TYPE_1__ git_apply_options ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_MODIFY_TWO_FILES ; 
 int /*<<< orphan*/  GIT_APPLY_LOCATION_WORKDIR ; 
 TYPE_1__ GIT_APPLY_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  delta_skip_cb ; 
 int /*<<< orphan*/  git_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_apply_workdir (int /*<<< orphan*/ ,struct merge_index_entry*,size_t) ; 
 int /*<<< orphan*/  validate_index_unchanged (int /*<<< orphan*/ ) ; 

void test_apply_callbacks__delta_can_skip(void)
{
	git_diff *diff;
	git_apply_options opts = GIT_APPLY_OPTIONS_INIT;

	struct merge_index_entry workdir_expected[] = {
		{ 0100644, "f51658077d85f2264fa179b4d0848268cb3475c3", 0, "asparagus.txt" },
		{ 0100644, "68f6182f4c85d39e1309d97c7e456156dc9c0096", 0, "beef.txt" },
		{ 0100644, "4b7c5650008b2e747fe1809eeb5a1dde0e80850a", 0, "bouilli.txt" },
		{ 0100644, "c4e6cca3ec6ae0148ed231f97257df8c311e015f", 0, "gravy.txt" },
		{ 0100644, "68af1fc7407fd9addf1701a87eb1c95c7494c598", 0, "oyster.txt" },
		{ 0100644, "a7b066537e6be7109abfe4ff97b675d4e077da20", 0, "veal.txt" },
	};
	size_t workdir_expected_cnt = sizeof(workdir_expected) /
	    sizeof(struct merge_index_entry);

	opts.delta_cb = delta_skip_cb;

	cl_git_pass(git_diff_from_buffer(&diff,
		DIFF_MODIFY_TWO_FILES, strlen(DIFF_MODIFY_TWO_FILES)));
	cl_git_pass(git_apply(repo, diff, GIT_APPLY_LOCATION_WORKDIR, &opts));

	validate_index_unchanged(repo);
	validate_apply_workdir(repo, workdir_expected, workdir_expected_cnt);

	git_diff_free(diff);
}