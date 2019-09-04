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
struct TYPE_6__ {int /*<<< orphan*/  conflicts; int /*<<< orphan*/  ignored; int /*<<< orphan*/  updates; int /*<<< orphan*/  dirty; int /*<<< orphan*/  untracked; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ notify_counts ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_7__ {int notify_flags; int checkout_strategy; TYPE_1__* notify_payload; int /*<<< orphan*/  notify_cb; } ;
typedef  TYPE_2__ git_checkout_options ;
typedef  int /*<<< orphan*/  cts ;

/* Variables and functions */
 int GIT_CHECKOUT_FORCE ; 
 int GIT_CHECKOUT_NOTIFY_CONFLICT ; 
 int GIT_CHECKOUT_NOTIFY_UNTRACKED ; 
 TYPE_2__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_REMOVE_UNTRACKED ; 
 int GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  GIT_RMDIR_REMOVE_FILES ; 
 int /*<<< orphan*/  assert_workdir_matches_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_create_file (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/ * g_typechange_expected_conflicts ; 
 int /*<<< orphan*/ * g_typechange_expected_untracked ; 
 int /*<<< orphan*/ ** g_typechange_oids ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_futils_rmdir_r (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_path_exists (char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_submodule_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_submodule_dirty ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  notify_counter ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_checkout_typechange__checkout_with_conflicts(void)
{
	int i;
	git_object *obj;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	notify_counts cts = {0};

	opts.notify_flags =
		GIT_CHECKOUT_NOTIFY_CONFLICT | GIT_CHECKOUT_NOTIFY_UNTRACKED;
	opts.notify_cb = notify_counter;
	opts.notify_payload = &cts;

	for (i = 0; g_typechange_oids[i] != NULL; ++i) {
		cl_git_pass(git_revparse_single(&obj, g_repo, g_typechange_oids[i]));

		force_create_file("typechanges/a/blocker");
		force_create_file("typechanges/b");
		force_create_file("typechanges/c/sub/sub/file");
		git_futils_rmdir_r("typechanges/d", NULL, GIT_RMDIR_REMOVE_FILES);
		p_mkdir("typechanges/d", 0777); /* intentionally empty dir */
		force_create_file("typechanges/untracked");
		cl_git_pass(git_submodule_foreach(g_repo, make_submodule_dirty, NULL));

		opts.checkout_strategy = GIT_CHECKOUT_SAFE;
		memset(&cts, 0, sizeof(cts));

		cl_git_fail(git_checkout_tree(g_repo, obj, &opts));
		cl_assert_equal_i(cts.conflicts, g_typechange_expected_conflicts[i]);
		cl_assert_equal_i(cts.untracked, g_typechange_expected_untracked[i]);
		cl_assert_equal_i(cts.dirty, 0);
		cl_assert_equal_i(cts.updates, 0);
		cl_assert_equal_i(cts.ignored, 0);

		opts.checkout_strategy =
			GIT_CHECKOUT_FORCE | GIT_CHECKOUT_REMOVE_UNTRACKED;
		memset(&cts, 0, sizeof(cts));

		cl_assert(git_path_exists("typechanges/untracked"));

		cl_git_pass(git_checkout_tree(g_repo, obj, &opts));
		cl_assert_equal_i(0, cts.conflicts);

		cl_assert(!git_path_exists("typechanges/untracked"));

		cl_git_pass(
			git_repository_set_head_detached(g_repo, git_object_id(obj)));

		assert_workdir_matches_tree(g_repo, git_object_id(obj), NULL, true);

		git_object_free(obj);
	}
}