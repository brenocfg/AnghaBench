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
struct TYPE_12__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  len; int /*<<< orphan*/  mode; int /*<<< orphan*/  path; int /*<<< orphan*/  automergeable; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_merge_file_result ;
struct TYPE_13__ {int /*<<< orphan*/  favor; } ;
typedef  TYPE_2__ git_merge_file_options ;
struct TYPE_14__ {char* ptr; int size; char* path; int mode; } ;
typedef  TYPE_3__ git_merge_file_input ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_MERGE_FILE_FAVOR_OURS ; 
 TYPE_3__ GIT_MERGE_FILE_INPUT_INIT ; 
 TYPE_2__ GIT_MERGE_FILE_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_merge_file (TYPE_1__*,TYPE_3__*,TYPE_3__*,TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  git_merge_file_result_free (TYPE_1__*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 

void test_merge_files__handles_binaries_when_favored(void)
{
	git_merge_file_input ancestor = GIT_MERGE_FILE_INPUT_INIT,
		ours = GIT_MERGE_FILE_INPUT_INIT,
		theirs = GIT_MERGE_FILE_INPUT_INIT;
	git_merge_file_options opts = GIT_MERGE_FILE_OPTIONS_INIT;
	git_merge_file_result result = {0};

	ancestor.ptr = "ance\0stor\0";
	ancestor.size = 10;
	ancestor.path = "ancestor.txt";
	ancestor.mode = 0100755;

	ours.ptr = "foo\0bar\0";
	ours.size = 8;
	ours.path = "ours.txt";
	ours.mode = 0100755;

	theirs.ptr = "bar\0foo\0";
	theirs.size = 8;
	theirs.path = "theirs.txt";
	theirs.mode = 0100644;

	opts.favor = GIT_MERGE_FILE_FAVOR_OURS;
	cl_git_pass(git_merge_file(&result, &ancestor, &ours, &theirs, &opts));

	cl_assert_equal_i(1, result.automergeable);

	cl_assert_equal_s("ours.txt", result.path);
	cl_assert_equal_i(0100755, result.mode);

	cl_assert_equal_i(ours.size, result.len);
	cl_assert(memcmp(result.ptr, ours.ptr, ours.size) == 0);

	git_merge_file_result_free(&result);
}