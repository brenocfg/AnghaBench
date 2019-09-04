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
typedef  int /*<<< orphan*/  workdir_expected ;
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  index_expected ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {int mode; char* path; int /*<<< orphan*/  id; TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 char* DIFF_MODIFY_TWO_FILES ; 
 int /*<<< orphan*/  GIT_APPLY_LOCATION_WORKDIR ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  validate_apply_index (int /*<<< orphan*/ ,struct merge_index_entry*,size_t) ; 
 int /*<<< orphan*/  validate_apply_workdir (int /*<<< orphan*/ ,struct merge_index_entry*,size_t) ; 

void test_apply_workdir__modified_index_with_unmodified_workdir_is_ok(void)
{
	git_index *index;
	git_index_entry idx_entry = {{0}};
	git_diff *diff;

	const char *diff_file = DIFF_MODIFY_TWO_FILES;

	struct merge_index_entry index_expected[] = {
		{ 0100644, "68f6182f4c85d39e1309d97c7e456156dc9c0096", 0, "beef.txt" },
		{ 0100644, "4b7c5650008b2e747fe1809eeb5a1dde0e80850a", 0, "bouilli.txt" },
		{ 0100644, "c4e6cca3ec6ae0148ed231f97257df8c311e015f", 0, "gravy.txt" },
		{ 0100644, "68af1fc7407fd9addf1701a87eb1c95c7494c598", 0, "oyster.txt" },
		{ 0100644, "ffb36e513f5fdf8a6ba850a20142676a2ac4807d", 0, "veal.txt" }
	};
	size_t index_expected_cnt = sizeof(index_expected) /
		sizeof(struct merge_index_entry);

	struct merge_index_entry workdir_expected[] = {
		{ 0100644, "ffb36e513f5fdf8a6ba850a20142676a2ac4807d", 0, "asparagus.txt" },
		{ 0100644, "68f6182f4c85d39e1309d97c7e456156dc9c0096", 0, "beef.txt" },
		{ 0100644, "4b7c5650008b2e747fe1809eeb5a1dde0e80850a", 0, "bouilli.txt" },
		{ 0100644, "c4e6cca3ec6ae0148ed231f97257df8c311e015f", 0, "gravy.txt" },
		{ 0100644, "68af1fc7407fd9addf1701a87eb1c95c7494c598", 0, "oyster.txt" },
		{ 0100644, "a7b066537e6be7109abfe4ff97b675d4e077da20", 0, "veal.txt" },
	};
	size_t workdir_expected_cnt = sizeof(workdir_expected) /
		sizeof(struct merge_index_entry);

	/* mutate the index and leave the workdir matching HEAD */
	cl_git_pass(git_repository_index(&index, repo));

	idx_entry.mode = 0100644;
	idx_entry.path = "veal.txt";
	cl_git_pass(git_oid_fromstr(&idx_entry.id, "ffb36e513f5fdf8a6ba850a20142676a2ac4807d"));

	cl_git_pass(git_index_add(index, &idx_entry));
	cl_git_pass(git_index_remove(index, "asparagus.txt", 0));
	cl_git_pass(git_index_write(index));

	cl_git_pass(git_diff_from_buffer(&diff, diff_file, strlen(diff_file)));
	cl_git_pass(git_apply(repo, diff, GIT_APPLY_LOCATION_WORKDIR, NULL));

	validate_apply_index(repo, index_expected, index_expected_cnt);
	validate_apply_workdir(repo, workdir_expected, workdir_expected_cnt);

	git_index_free(index);
	git_diff_free(diff);
}