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
typedef  scalar_t__ git_treewalk_mode ;
typedef  int /*<<< orphan*/  git_treewalk_cb ;
typedef  int /*<<< orphan*/  git_tree ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 scalar_t__ GIT_TREEWALK_POST ; 
 scalar_t__ GIT_TREEWALK_PRE ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int tree_walk (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int) ; 

int git_tree_walk(
	const git_tree *tree,
	git_treewalk_mode mode,
	git_treewalk_cb callback,
	void *payload)
{
	int error = 0;
	git_buf root_path = GIT_BUF_INIT;

	if (mode != GIT_TREEWALK_POST && mode != GIT_TREEWALK_PRE) {
		git_error_set(GIT_ERROR_INVALID, "invalid walking mode for tree walk");
		return -1;
	}

	error = tree_walk(
		tree, callback, &root_path, payload, (mode == GIT_TREEWALK_PRE));

	git_buf_dispose(&root_path);

	return error;
}