#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; int /*<<< orphan*/  automergeable; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_result ;
struct TYPE_13__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ git_merge_file_options ;
struct TYPE_14__ {char* ptr; int size; char* path; int mode; } ;
typedef  TYPE_3__ git_merge_file_input ;

/* Variables and functions */
 TYPE_3__ GIT_MERGE_FILE_INPUT_INIT ; 
 TYPE_2__ GIT_MERGE_FILE_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_MERGE_FILE_STYLE_DIFF3 ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_file (TYPE_1__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_1__*) ; 
 scalar_t__ memcmp (char const*,int /*<<< orphan*/ ,size_t) ; 
 size_t strlen (char const*) ; 

void test_merge_files__crlf_conflict_markers_for_crlf_files(void)
{
	git_merge_file_input ancestor = GIT_MERGE_FILE_INPUT_INIT,
		ours = GIT_MERGE_FILE_INPUT_INIT,
		theirs = GIT_MERGE_FILE_INPUT_INIT;
	git_merge_file_options opts = GIT_MERGE_FILE_OPTIONS_INIT;
	git_merge_file_result result = {0};

	const char *expected =
		"<<<<<<< file.txt\r\nThis file\r\ndoes, too.\r\n"
		"=======\r\nAnd so does\r\nthis one.\r\n>>>>>>> file.txt\r\n";
	size_t expected_len = strlen(expected);

	const char *expected_diff3 =
		"<<<<<<< file.txt\r\nThis file\r\ndoes, too.\r\n"
		"||||||| file.txt\r\nThis file has\r\nCRLF line endings.\r\n"
		"=======\r\nAnd so does\r\nthis one.\r\n>>>>>>> file.txt\r\n";
	size_t expected_diff3_len = strlen(expected_diff3);

	ancestor.ptr = "This file has\r\nCRLF line endings.\r\n";
	ancestor.size = 35;
	ancestor.path = "file.txt";
	ancestor.mode = 0100644;

	ours.ptr = "This file\r\ndoes, too.\r\n";
	ours.size = 23;
	ours.path = "file.txt";
	ours.mode = 0100644;

	theirs.ptr = "And so does\r\nthis one.\r\n";
	theirs.size = 24;
	theirs.path = "file.txt";
	theirs.mode = 0100644;

	cl_git_pass(git_merge_file(&result, &ancestor, &ours, &theirs, &opts));
	cl_assert_equal_i(0, result.automergeable);
	cl_assert_equal_i(expected_len, result.len);
	cl_assert(memcmp(expected, result.ptr, expected_len) == 0);
	git_merge_file_result_free(&result);

	opts.flags |= GIT_MERGE_FILE_STYLE_DIFF3;
	cl_git_pass(git_merge_file(&result, &ancestor, &ours, &theirs, &opts));
	cl_assert_equal_i(0, result.automergeable);
	cl_assert_equal_i(expected_diff3_len, result.len);
	cl_assert(memcmp(expected_diff3, result.ptr, expected_len) == 0);
	git_merge_file_result_free(&result);
}