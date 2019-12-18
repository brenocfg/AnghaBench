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
struct owner_graph {int dummy; } ;
struct lockf_entry {TYPE_1__* lf_owner; } ;
struct TYPE_2__ {int /*<<< orphan*/  lo_vertex; } ;

/* Variables and functions */
 int /*<<< orphan*/  graph_alloc_vertex (struct owner_graph*,TYPE_1__*) ; 
 struct owner_graph lf_owner_graph ; 

__attribute__((used)) static void
lf_alloc_vertex(struct lockf_entry *lock)
{
	struct owner_graph *g = &lf_owner_graph;

	if (!lock->lf_owner->lo_vertex)
		lock->lf_owner->lo_vertex =
			graph_alloc_vertex(g, lock->lf_owner);
}