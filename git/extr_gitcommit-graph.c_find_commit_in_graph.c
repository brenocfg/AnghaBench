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
struct commit_graph {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  oid; } ;
struct commit {scalar_t__ graph_pos; TYPE_1__ object; } ;

/* Variables and functions */
 scalar_t__ COMMIT_NOT_FROM_GRAPH ; 
 int bsearch_graph (struct commit_graph*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static int find_commit_in_graph(struct commit *item, struct commit_graph *g, uint32_t *pos)
{
	if (item->graph_pos != COMMIT_NOT_FROM_GRAPH) {
		*pos = item->graph_pos;
		return 1;
	} else {
		return bsearch_graph(g, &(item->object.oid), pos);
	}
}