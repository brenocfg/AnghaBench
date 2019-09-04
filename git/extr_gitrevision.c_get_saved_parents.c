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
struct rev_info {int /*<<< orphan*/  saved_parents_slab; } ;
struct commit_list {int dummy; } ;
struct commit {struct commit_list* parents; } ;

/* Variables and functions */
 struct commit_list* EMPTY_PARENT_LIST ; 
 struct commit_list** saved_parents_at (int /*<<< orphan*/ ,struct commit const*) ; 

struct commit_list *get_saved_parents(struct rev_info *revs, const struct commit *commit)
{
	struct commit_list *parents;

	if (!revs->saved_parents_slab)
		return commit->parents;

	parents = *saved_parents_at(revs->saved_parents_slab, commit);
	if (parents == EMPTY_PARENT_LIST)
		return NULL;
	return parents;
}