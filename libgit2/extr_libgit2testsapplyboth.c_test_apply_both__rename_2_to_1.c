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
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  both_expected ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_RENAME_2_TO_1 ; 
 int /*<<< orphan*/  GIT_APPLY_LOCATION_BOTH ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_apply_index (int /*<<< orphan*/ ,struct merge_index_entry*,size_t) ; 
 int /*<<< orphan*/  validate_apply_workdir (int /*<<< orphan*/ ,struct merge_index_entry*,size_t) ; 

void test_apply_both__rename_2_to_1(void)
{
	git_diff *diff;

	struct merge_index_entry both_expected[] = {
		{ 0100644, "68f6182f4c85d39e1309d97c7e456156dc9c0096", 0, "2.txt" },
		{ 0100644, "4b7c5650008b2e747fe1809eeb5a1dde0e80850a", 0, "bouilli.txt" },
		{ 0100644, "c4e6cca3ec6ae0148ed231f97257df8c311e015f", 0, "gravy.txt" },
		{ 0100644, "68af1fc7407fd9addf1701a87eb1c95c7494c598", 0, "oyster.txt" },
		{ 0100644, "94d2c01087f48213bd157222d54edfefd77c9bba", 0, "veal.txt" }
	};
	size_t both_expected_cnt = sizeof(both_expected) /
		sizeof(struct merge_index_entry);

	cl_git_pass(git_diff_from_buffer(&diff, DIFF_RENAME_2_TO_1,
		strlen(DIFF_RENAME_2_TO_1)));
	cl_git_pass(git_apply(repo, diff, GIT_APPLY_LOCATION_BOTH, NULL));

	validate_apply_index(repo, both_expected, both_expected_cnt);
	validate_apply_workdir(repo, both_expected, both_expected_cnt);

	git_diff_free(diff);
}