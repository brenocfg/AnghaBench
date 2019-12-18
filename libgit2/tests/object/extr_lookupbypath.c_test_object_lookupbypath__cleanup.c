#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/ * g_actualobject ; 
 int /*<<< orphan*/ * g_expectedobject ; 
 int /*<<< orphan*/  g_head_commit ; 
 int /*<<< orphan*/ * g_repo ; 
 int /*<<< orphan*/  g_root_tree ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_object_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ ) ; 

void test_object_lookupbypath__cleanup(void)
{
	git_object_free(g_actualobject);
	git_object_free(g_expectedobject);
	git_tree_free(g_root_tree);
	git_commit_free(g_head_commit);
	g_expectedobject = NULL;
	git_repository_free(g_repo);
	g_repo = NULL;
}