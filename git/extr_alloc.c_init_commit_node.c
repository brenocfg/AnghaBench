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
struct repository {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;
struct commit {int /*<<< orphan*/  generation; int /*<<< orphan*/  graph_pos; int /*<<< orphan*/  index; TYPE_1__ object; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMMIT_NOT_FROM_GRAPH ; 
 int /*<<< orphan*/  GENERATION_NUMBER_INFINITY ; 
 int /*<<< orphan*/  OBJ_COMMIT ; 
 int /*<<< orphan*/  alloc_commit_index (struct repository*) ; 

void init_commit_node(struct repository *r, struct commit *c)
{
	c->object.type = OBJ_COMMIT;
	c->index = alloc_commit_index(r);
	c->graph_pos = COMMIT_NOT_FROM_GRAPH;
	c->generation = GENERATION_NUMBER_INFINITY;
}