#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_diff_delta ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_3__ {int /*<<< orphan*/  files; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ diff_expects ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  diff_file_cb (int /*<<< orphan*/  const*,float,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_diff_get_delta (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 

void test_diff_diffiter__iterate_files_1(void)
{
	git_repository *repo = cl_git_sandbox_init("attr");
	git_diff *diff;
	size_t d, num_d;
	diff_expects exp = { 0 };

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, NULL));

	num_d = git_diff_num_deltas(diff);

	for (d = 0; d < num_d; ++d) {
		const git_diff_delta *delta = git_diff_get_delta(diff, d);
		cl_assert(delta != NULL);

		diff_file_cb(delta, (float)d / (float)num_d, &exp);
	}
	cl_assert_equal_sz(6, exp.files);

	git_diff_free(diff);
}