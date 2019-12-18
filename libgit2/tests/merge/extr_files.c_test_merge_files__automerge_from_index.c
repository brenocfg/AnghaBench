#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; int /*<<< orphan*/  automergeable; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_result ;
struct TYPE_9__ {char* path; int mode; int /*<<< orphan*/  id; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  AUTOMERGEABLE_MERGED_FILE ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_file_from_index (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_1__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  repo ; 
 int strlen (int /*<<< orphan*/ ) ; 

void test_merge_files__automerge_from_index(void)
{
	git_merge_file_result result = {0};
	git_index_entry ancestor, ours, theirs;

	git_oid_fromstr(&ancestor.id, "6212c31dab5e482247d7977e4f0dd3601decf13b");
	ancestor.path = "automergeable.txt";
	ancestor.mode = 0100644;

	git_oid_fromstr(&ours.id, "ee3fa1b8c00aff7fe02065fdb50864bb0d932ccf");
	ours.path = "automergeable.txt";
	ours.mode = 0100755;

	git_oid_fromstr(&theirs.id, "058541fc37114bfc1dddf6bd6bffc7fae5c2e6fe");
	theirs.path = "newname.txt";
	theirs.mode = 0100644;

	cl_git_pass(git_merge_file_from_index(&result, repo,
		&ancestor, &ours, &theirs, 0));

	cl_assert_equal_i(1, result.automergeable);

	cl_assert_equal_s("newname.txt", result.path);
	cl_assert_equal_i(0100755, result.mode);

	cl_assert_equal_i(strlen(AUTOMERGEABLE_MERGED_FILE), result.len);
	cl_assert_equal_strn(AUTOMERGEABLE_MERGED_FILE, result.ptr, result.len);

	git_merge_file_result_free(&result);
}