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
struct merge_index_entry {int member_0; char* member_1; char* member_3; int /*<<< orphan*/  member_2; } ;
typedef  int /*<<< orphan*/  index_expected ;
struct TYPE_4__ {int mode; char* path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 char* DIFF_MODIFY_TWO_FILES ; 
 int /*<<< orphan*/  GIT_APPLY_LOCATION_INDEX ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  validate_apply_index (int /*<<< orphan*/ ,struct merge_index_entry*,size_t) ; 
 int /*<<< orphan*/  validate_workdir_unchanged (int /*<<< orphan*/ ) ; 

void test_apply_index__keeps_nonconflicting_changes(void)
{
	git_diff *diff;
	git_index *index;
	git_index_entry idx_entry;

	const char *diff_file = DIFF_MODIFY_TWO_FILES;

	struct merge_index_entry index_expected[] = {
		{ 0100644, "ffb36e513f5fdf8a6ba850a20142676a2ac4807d", 0, "asparagus.txt" },
		{ 0100644, "898d12687fb35be271c27c795a6b32c8b51da79e", 0, "beef.txt" },
		{ 0100644, "c4e6cca3ec6ae0148ed231f97257df8c311e015f", 0, "gravy.txt" },
		{ 0100644, "68af1fc7407fd9addf1701a87eb1c95c7494c598", 0, "oyster.txt" },
		{ 0100644, "a7b066537e6be7109abfe4ff97b675d4e077da20", 0, "veal.txt" },
	};
	size_t index_expected_cnt = sizeof(index_expected) /
		sizeof(struct merge_index_entry);

	/* mutate the index */
	cl_git_pass(git_repository_index(&index, repo));

	memset(&idx_entry, 0, sizeof(git_index_entry));
	idx_entry.mode = 0100644;
	idx_entry.path = "beef.txt";
	cl_git_pass(git_oid_fromstr(&idx_entry.id, "898d12687fb35be271c27c795a6b32c8b51da79e"));
	cl_git_pass(git_index_add(index, &idx_entry));

	cl_git_pass(git_index_remove(index, "bouilli.txt", 0));
	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_git_pass(git_diff_from_buffer(&diff, diff_file, strlen(diff_file)));
	cl_git_pass(git_apply(repo, diff, GIT_APPLY_LOCATION_INDEX, NULL));

	validate_apply_index(repo, index_expected, index_expected_cnt);
	validate_workdir_unchanged(repo);

	git_diff_free(diff);
}