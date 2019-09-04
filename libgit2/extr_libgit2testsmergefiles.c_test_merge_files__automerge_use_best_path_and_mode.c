#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  len; int /*<<< orphan*/  ptr; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; int /*<<< orphan*/  automergeable; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_result ;
struct TYPE_10__ {char* ptr; int size; char* path; int mode; } ;
typedef  TYPE_2__ git_merge_file_input ;

/* Variables and functions */
 TYPE_2__ GIT_MERGE_FILE_INPUT_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_file (TYPE_1__*,TYPE_2__*,TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_1__*) ; 
 int strlen (char const*) ; 

void test_merge_files__automerge_use_best_path_and_mode(void)
{
	git_merge_file_input ancestor = GIT_MERGE_FILE_INPUT_INIT,
		ours = GIT_MERGE_FILE_INPUT_INIT,
		theirs = GIT_MERGE_FILE_INPUT_INIT;
	git_merge_file_result result = {0};
	const char *expected = "Zero\n1\n2\n3\n4\n5\n6\n7\n8\n9\nTen\n";

	ancestor.ptr = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";
	ancestor.size = strlen(ancestor.ptr);
	ancestor.path = "testfile.txt";
	ancestor.mode = 0100755;

	ours.ptr = "Zero\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n";
	ours.size = strlen(ours.ptr);
	ours.path = "testfile.txt";
	ours.mode = 0100644;

	theirs.ptr = "0\n1\n2\n3\n4\n5\n6\n7\n8\n9\nTen\n";
	theirs.size = strlen(theirs.ptr);
	theirs.path = "theirs.txt";
	theirs.mode = 0100755;

	cl_git_pass(git_merge_file(&result, &ancestor, &ours, &theirs, 0));

	cl_assert_equal_i(1, result.automergeable);

	cl_assert_equal_s("theirs.txt", result.path);
	cl_assert_equal_i(0100644, result.mode);

	cl_assert_equal_i(strlen(expected), result.len);
	cl_assert_equal_strn(expected, result.ptr, result.len);

	git_merge_file_result_free(&result);
}