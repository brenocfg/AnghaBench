#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_9__ {char** strings; int count; } ;
struct TYPE_10__ {TYPE_1__ paths; int /*<<< orphan*/  checkout_strategy; int /*<<< orphan*/  progress_cb; } ;
typedef  TYPE_2__ git_checkout_options ;
struct TYPE_11__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_3__ git_buf ;

/* Variables and functions */
 TYPE_3__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_2__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_strn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_3__*) ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_futils_readbuffer (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  update_attr_callback ; 

void test_checkout_tree__caches_attributes_during_checkout(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	git_object *obj = NULL;
	git_buf ident1 = GIT_BUF_INIT, ident2 = GIT_BUF_INIT;
	char *ident_paths[] = { "ident1.txt", "ident2.txt" };

	opts.progress_cb = update_attr_callback;

	assert_on_branch(g_repo, "master");
	opts.checkout_strategy = GIT_CHECKOUT_FORCE;
	opts.paths.strings = ident_paths;
	opts.paths.count = 2;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/ident"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

	cl_git_pass(git_futils_readbuffer(&ident1, "testrepo/ident1.txt"));
	cl_git_pass(git_futils_readbuffer(&ident2, "testrepo/ident2.txt"));

	cl_assert_equal_strn(ident1.ptr, "# $Id$", 6);
	cl_assert_equal_strn(ident2.ptr, "# $Id$", 6);

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

	cl_git_pass(git_futils_readbuffer(&ident1, "testrepo/ident1.txt"));
	cl_git_pass(git_futils_readbuffer(&ident2, "testrepo/ident2.txt"));

	cl_assert_equal_strn(ident1.ptr, "# $Id: ", 7);
	cl_assert_equal_strn(ident2.ptr, "# $Id: ", 7);

	git_buf_dispose(&ident1);
	git_buf_dispose(&ident2);
	git_object_free(obj);
}