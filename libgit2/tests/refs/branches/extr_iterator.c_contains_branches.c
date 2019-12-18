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
struct expectations {int /*<<< orphan*/  encounters; int /*<<< orphan*/  branch_name; } ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_branch_t ;
typedef  int /*<<< orphan*/  git_branch_iterator ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int git_branch_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_shorthand (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void contains_branches(struct expectations exp[], git_branch_iterator *iter)
{
	git_reference *ref;
	git_branch_t type;
	int error, pos = 0;

	while ((error = git_branch_next(&ref, &type, iter)) == 0) {
		for (pos = 0; exp[pos].branch_name; ++pos) {
			if (strcmp(git_reference_shorthand(ref), exp[pos].branch_name) == 0)
				exp[pos].encounters++;
		}

		git_reference_free(ref);
	}

	cl_assert_equal_i(error, GIT_ITEROVER);
}