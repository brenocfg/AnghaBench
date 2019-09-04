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
 int /*<<< orphan*/ * _a ; 
 int /*<<< orphan*/ * _b ; 
 scalar_t__ _check_counts ; 
 int /*<<< orphan*/ * _counts ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_atomic_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_tree_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void free_trees(void)
{
	git_tree_free(_a); _a = NULL;
	git_tree_free(_b); _b = NULL;

	if (_check_counts) {
		cl_assert_equal_i(288, git_atomic_get(&_counts[0]));
		cl_assert_equal_i(112, git_atomic_get(&_counts[1]));
		cl_assert_equal_i( 80, git_atomic_get(&_counts[2]));
		cl_assert_equal_i( 96, git_atomic_get(&_counts[3]));
	}
}