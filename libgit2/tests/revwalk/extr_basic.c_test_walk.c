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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ *,int) ; 
 int test_walk_only (int /*<<< orphan*/ *,int const**,int) ; 

__attribute__((used)) static int test_walk(git_revwalk *walk, const git_oid *root,
		int flags, const int possible_results[][6], int results_count)
{
	git_revwalk_sorting(walk, flags);
	git_revwalk_push(walk, root);

	return test_walk_only(walk, possible_results, results_count);
}