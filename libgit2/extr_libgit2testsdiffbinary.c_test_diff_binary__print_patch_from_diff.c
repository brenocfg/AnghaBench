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
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  id_abbrev; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_9__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_2__ git_buf ;

/* Variables and functions */
 TYPE_2__ GIT_BUF_INIT ; 
 int GIT_DIFF_FORCE_BINARY ; 
 int /*<<< orphan*/  GIT_DIFF_FORMAT_PATCH ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int GIT_DIFF_SHOW_BINARY ; 
 int /*<<< orphan*/  GIT_OID_HEXSZ ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_2__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_print (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_cb ; 
 int /*<<< orphan*/  repo ; 

void test_diff_binary__print_patch_from_diff(void)
{
	git_index *index;
	git_diff *diff;
	git_buf actual = GIT_BUF_INIT;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	const char *expected =
		"diff --git a/untimely.txt b/untimely.txt\n" \
		"index 9a69d960ae94b060f56c2a8702545e2bb1abb935..1111d4f11f4b35bf6759e0fb714fe09731ef0840 100644\n" \
		"GIT binary patch\n" \
		"delta 32\n" \
		"nc%1vf+QYWt3zLL@hC)e3Vu?a>QDRl4f_G*?PG(-ZA}<#J$+QbW\n" \
		"\n" \
		"delta 7\n" \
		"Oc%18D`@*{63ljhg(E~C7\n" \
		"\n";

	opts.flags = GIT_DIFF_SHOW_BINARY | GIT_DIFF_FORCE_BINARY;
	opts.id_abbrev = GIT_OID_HEXSZ;

	repo = cl_git_sandbox_init("renames");
	cl_git_pass(git_repository_index(&index, repo));

	cl_git_append2file("renames/untimely.txt", "Oh that crazy Kipling!\r\n");

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, index, &opts));

	cl_git_pass(git_diff_print(diff, GIT_DIFF_FORMAT_PATCH, print_cb, &actual));

	cl_assert_equal_s(expected, actual.ptr);

	git_buf_dispose(&actual);
	git_diff_free(diff);
	git_index_free(index);
}