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
struct rev_info {int /*<<< orphan*/  first_parent_only; int /*<<< orphan*/  simplify_history; scalar_t__ dense; scalar_t__ prune; } ;

/* Variables and functions */

__attribute__((used)) static inline int limiting_can_increase_treesame(const struct rev_info *revs)
{
	/*
	 * TREESAME is irrelevant unless prune && dense;
	 * if simplify_history is set, we can't have a mixture of TREESAME and
	 *    !TREESAME INTERESTING parents (and we don't have treesame[]
	 *    decoration anyway);
	 * if first_parent_only is set, then the TREESAME flag is locked
	 *    against the first parent (and again we lack treesame[] decoration).
	 */
	return revs->prune && revs->dense &&
	       !revs->simplify_history &&
	       !revs->first_parent_only;
}