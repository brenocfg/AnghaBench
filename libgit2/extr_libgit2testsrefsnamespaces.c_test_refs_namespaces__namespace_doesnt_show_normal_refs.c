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
struct TYPE_4__ {int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ git_strarray ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_reference_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_set_namespace (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_strarray_free (TYPE_1__*) ; 

void test_refs_namespaces__namespace_doesnt_show_normal_refs(void)
{
	static git_strarray ref_list;

	cl_git_pass(git_repository_set_namespace(g_repo, "namespace"));
	cl_git_pass(git_reference_list(&ref_list, g_repo));
	cl_assert_equal_i(0, ref_list.count);
	git_strarray_free(&ref_list);
}