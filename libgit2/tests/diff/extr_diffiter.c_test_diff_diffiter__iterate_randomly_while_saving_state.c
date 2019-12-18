#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  patches ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_patch ;
struct TYPE_6__ {int context_lines; int interhunk_lines; int flags; } ;
typedef  TYPE_1__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;
struct TYPE_7__ {int /*<<< orphan*/  lines; int /*<<< orphan*/  hunks; int /*<<< orphan*/  files; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ diff_expects ;

/* Variables and functions */
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_1__ GIT_DIFF_OPTIONS_INIT ; 
 int PATCH_CACHE ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 size_t git_diff_num_deltas (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_patch_from_diff (int /*<<< orphan*/ **,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  iterate_over_patch (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int) ; 
 int rand () ; 
 int /*<<< orphan*/  srand (int) ; 

void test_diff_diffiter__iterate_randomly_while_saving_state(void)
{
	git_repository *repo = cl_git_sandbox_init("status");
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	diff_expects exp = {0};
	git_patch *patches[PATCH_CACHE];
	size_t p, d, num_d;

	memset(patches, 0, sizeof(patches));

	opts.context_lines = 3;
	opts.interhunk_lines = 1;
	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;

	cl_git_pass(git_diff_index_to_workdir(&diff, repo, NULL, &opts));

	num_d = git_diff_num_deltas(diff);

	/* To make sure that references counts work for diff and patch objects,
	 * this generates patches and randomly caches them.  Only when the patch
	 * is removed from the cache are hunks and lines counted.  At the end,
	 * there are still patches in the cache, so free the diff and try to
	 * process remaining patches after the diff is freed.
	 */

	srand(121212);
	p = rand() % PATCH_CACHE;

	for (d = 0; d < num_d; ++d) {
		/* take old patch */
		git_patch *patch = patches[p];
		patches[p] = NULL;

		/* cache new patch */
		cl_git_pass(git_patch_from_diff(&patches[p], diff, d));
		cl_assert(patches[p] != NULL);

		/* process old patch if non-NULL */
		if (patch != NULL) {
			iterate_over_patch(patch, &exp);
			git_patch_free(patch);
		}

		p = rand() % PATCH_CACHE;
	}

	/* free diff list now - refcounts should keep things safe */
	git_diff_free(diff);

	/* process remaining unprocessed patches */
	for (p = 0; p < PATCH_CACHE; p++) {
		git_patch *patch = patches[p];

		if (patch != NULL) {
			iterate_over_patch(patch, &exp);
			git_patch_free(patch);
		}
	}

	/* hopefully it all still added up right */
	cl_assert_equal_i(13, exp.files);
	cl_assert_equal_i(8, exp.hunks);
	cl_assert_equal_i(14, exp.lines);
}