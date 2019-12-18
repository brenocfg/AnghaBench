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
struct git_graph {int mapping_size; int* mapping; } ;

/* Variables and functions */

__attribute__((used)) static int graph_is_mapping_correct(struct git_graph *graph)
{
	int i;

	/*
	 * The mapping is up to date if each entry is at its target,
	 * or is 1 greater than its target.
	 * (If it is 1 greater than the target, '/' will be printed, so it
	 * will look correct on the next row.)
	 */
	for (i = 0; i < graph->mapping_size; i++) {
		int target = graph->mapping[i];
		if (target < 0)
			continue;
		if (target == (i / 2))
			continue;
		return 0;
	}

	return 1;
}