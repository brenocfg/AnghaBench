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
struct tree {int dummy; } ;
struct merge_options {int /*<<< orphan*/ * ancestor; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_finalize (struct merge_options*) ; 
 scalar_t__ merge_start (struct merge_options*,struct tree*) ; 
 int merge_trees_internal (struct merge_options*,struct tree*,struct tree*,struct tree*,struct tree**) ; 

int merge_trees(struct merge_options *opt,
		struct tree *head,
		struct tree *merge,
		struct tree *merge_base)
{
	int clean;
	struct tree *ignored;

	assert(opt->ancestor != NULL);

	if (merge_start(opt, head))
		return -1;
	clean = merge_trees_internal(opt, head, merge, merge_base, &ignored);
	merge_finalize(opt);

	return clean;
}