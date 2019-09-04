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
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_4__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_SAFE ; 
 int /*<<< orphan*/  assert_workdir_matches_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/ * g_typechange_empty ; 
 int /*<<< orphan*/ ** g_typechange_oids ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_id (int /*<<< orphan*/ *) ; 
 int git_path_exists (char*) ; 
 int git_path_isdir (char*) ; 
 int /*<<< orphan*/  git_repository_set_head_detached (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revparse_single (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_checkout_typechange__checkout_typechanges_safe(void)
{
	int i;
	git_object *obj;
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;

	for (i = 0; g_typechange_oids[i] != NULL; ++i) {
		cl_git_pass(git_revparse_single(&obj, g_repo, g_typechange_oids[i]));

		opts.checkout_strategy = !i ? GIT_CHECKOUT_FORCE : GIT_CHECKOUT_SAFE;

		cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

		cl_git_pass(
			git_repository_set_head_detached(g_repo, git_object_id(obj)));

		assert_workdir_matches_tree(g_repo, git_object_id(obj), NULL, true);

		git_object_free(obj);

		if (!g_typechange_empty[i]) {
			cl_assert(git_path_isdir("typechanges"));
			cl_assert(git_path_exists("typechanges/a"));
			cl_assert(git_path_exists("typechanges/b"));
			cl_assert(git_path_exists("typechanges/c"));
			cl_assert(git_path_exists("typechanges/d"));
			cl_assert(git_path_exists("typechanges/e"));
		} else {
			cl_assert(git_path_isdir("typechanges"));
			cl_assert(!git_path_exists("typechanges/a"));
			cl_assert(!git_path_exists("typechanges/b"));
			cl_assert(!git_path_exists("typechanges/c"));
			cl_assert(!git_path_exists("typechanges/d"));
			cl_assert(!git_path_exists("typechanges/e"));
		}
	}
}