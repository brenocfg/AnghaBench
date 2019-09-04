#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_index ;
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_DIFF_REVERSE ; 
 int /*<<< orphan*/  _a ; 
 int /*<<< orphan*/  _b ; 
 int /*<<< orphan*/  _repo ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_tree_to_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_remove_bypath (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_thread_yield () ; 

__attribute__((used)) static void *run_index_diffs_with_modifier(void *arg)
{
	int thread = *(int *)arg;
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	git_index *idx = NULL;
	git_repository *repo;

	cl_git_pass(git_repository_open(&repo, git_repository_path(_repo)));
	cl_git_pass(git_repository_index(&idx, repo));

	/* have first thread altering the index as we go */
	if (thread == 0) {
		int i;

		for (i = 0; i < 300; ++i) {
			switch (i & 0x03) {
			case 0: (void)git_index_add_bypath(idx, "new_file"); break;
			case 1: (void)git_index_remove_bypath(idx, "modified_file"); break;
			case 2: (void)git_index_remove_bypath(idx, "new_file"); break;
			case 3: (void)git_index_add_bypath(idx, "modified_file"); break;
			}
			git_thread_yield();
		}

		goto done;
	}

	/* only use explicit index in this test to prevent reloading */

	switch (thread & 0x03) {
	case 0: /* diff index to workdir */;
		cl_git_pass(git_diff_index_to_workdir(&diff, repo, idx, &opts));
		break;
	case 1: /* diff tree 'a' to index */;
		cl_git_pass(git_diff_tree_to_index(&diff, repo, _a, idx, &opts));
		break;
	case 2: /* diff tree 'b' to index */;
		cl_git_pass(git_diff_tree_to_index(&diff, repo, _b, idx, &opts));
		break;
	case 3: /* diff index to workdir reversed */;
		opts.flags |= GIT_DIFF_REVERSE;
		cl_git_pass(git_diff_index_to_workdir(&diff, repo, idx, &opts));
		break;
	}

	/* results will be unpredictable with index modifier thread running */

	git_diff_free(diff);

done:
	git_index_free(idx);
	git_repository_free(repo);
	git_error_clear();

	return arg;
}