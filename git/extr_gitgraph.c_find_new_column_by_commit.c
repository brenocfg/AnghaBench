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
struct git_graph {int num_new_columns; struct column* new_columns; } ;
struct commit {int dummy; } ;
struct column {struct commit* commit; } ;

/* Variables and functions */

__attribute__((used)) static struct column *find_new_column_by_commit(struct git_graph *graph,
						struct commit *commit)
{
	int i;
	for (i = 0; i < graph->num_new_columns; i++) {
		if (graph->new_columns[i].commit == commit)
			return &graph->new_columns[i];
	}
	return NULL;
}