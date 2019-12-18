#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct repository {int dummy; } ;
struct commit_list {int dummy; } ;
struct TYPE_2__ {int flags; } ;
struct commit {scalar_t__ generation; TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ GENERATION_NUMBER_INFINITY ; 
 int PARENT2 ; 
 int /*<<< orphan*/  all_flags ; 
 int /*<<< orphan*/  clear_commit_marks (struct commit*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_commit_marks_many (int,struct commit**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_commit_list (struct commit_list*) ; 
 struct commit_list* paint_down_to_common (struct repository*,struct commit*,int,struct commit**,scalar_t__) ; 
 scalar_t__ repo_parse_commit (struct repository*,struct commit*) ; 

int repo_in_merge_bases_many(struct repository *r, struct commit *commit,
			     int nr_reference, struct commit **reference)
{
	struct commit_list *bases;
	int ret = 0, i;
	uint32_t min_generation = GENERATION_NUMBER_INFINITY;

	if (repo_parse_commit(r, commit))
		return ret;
	for (i = 0; i < nr_reference; i++) {
		if (repo_parse_commit(r, reference[i]))
			return ret;
		if (reference[i]->generation < min_generation)
			min_generation = reference[i]->generation;
	}

	if (commit->generation > min_generation)
		return ret;

	bases = paint_down_to_common(r, commit,
				     nr_reference, reference,
				     commit->generation);
	if (commit->object.flags & PARENT2)
		ret = 1;
	clear_commit_marks(commit, all_flags);
	clear_commit_marks_many(nr_reference, reference, all_flags);
	free_commit_list(bases);
	return ret;
}