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
struct TYPE_4__ {int mode; char* path; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_index_entry ;
typedef  int /*<<< orphan*/  git_index ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 char* DIFF_MODIFY_TWO_FILES ; 
 int /*<<< orphan*/  GIT_APPLY_LOCATION_BOTH ; 
 int /*<<< orphan*/  GIT_EAPPLYFAIL ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_apply (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_from_buffer (int /*<<< orphan*/ **,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_add (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  strlen (char const*) ; 

void test_apply_both__index_must_match_workdir(void)
{
	git_diff *diff;
	git_index *index;
	git_index_entry idx_entry;

	const char *diff_file = DIFF_MODIFY_TWO_FILES;

	/*
	 * Append a line to the end of the file in both the index and the
	 * working directory.  Although the appended line would allow for
	 * patch application in each, the line appended is different in
	 * each, so the application should not be allowed.
	 */
	cl_git_append2file("merge-recursive/asparagus.txt",
	    "This is a modification.\n");

	cl_git_pass(git_repository_index(&index, repo));

	memset(&idx_entry, 0, sizeof(git_index_entry));
	idx_entry.mode = 0100644;
	idx_entry.path = "asparagus.txt";
	cl_git_pass(git_oid_fromstr(&idx_entry.id, "06d3fefb8726ab1099acc76e02dfb85e034b2538"));
	cl_git_pass(git_index_add(index, &idx_entry));

	cl_git_pass(git_index_write(index));
	git_index_free(index);

	cl_git_pass(git_diff_from_buffer(&diff, diff_file, strlen(diff_file)));
	cl_git_fail_with(GIT_EAPPLYFAIL, git_apply(repo, diff, GIT_APPLY_LOCATION_BOTH, NULL));

	git_diff_free(diff);
}