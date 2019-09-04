#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_object ;
struct TYPE_5__ {scalar_t__ mkdir_calls; scalar_t__ stat_calls; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ git_checkout_perfdata ;
struct TYPE_6__ {int /*<<< orphan*/  checkout_strategy; TYPE_1__* perfdata_payload; int /*<<< orphan*/  perfdata_cb; } ;
typedef  TYPE_2__ git_checkout_options ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_2__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_OBJECT_ANY ; 
 int /*<<< orphan*/  assert_on_branch (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_object_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  perfdata_cb ; 

void test_checkout_tree__can_collect_perfdata(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	git_oid oid;
	git_object *obj = NULL;
	git_checkout_perfdata perfdata = {0};

	opts.perfdata_cb = perfdata_cb;
	opts.perfdata_payload = &perfdata;

	assert_on_branch(g_repo, "master");
	opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_reference_name_to_id(&oid, g_repo, "refs/heads/dir"));
	cl_git_pass(git_object_lookup(&obj, g_repo, &oid, GIT_OBJECT_ANY));

	cl_git_pass(git_checkout_tree(g_repo, obj, &opts));

	cl_assert(perfdata.mkdir_calls > 0);
	cl_assert(perfdata.stat_calls > 0);

	git_object_free(obj);
}