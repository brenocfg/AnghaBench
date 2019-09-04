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
struct topo_walk_info {int /*<<< orphan*/  indegree; int /*<<< orphan*/  topo_queue; } ;
struct rev_info {struct topo_walk_info* topo_walk_info; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 scalar_t__* indegree_slab_at (int /*<<< orphan*/ *,struct commit*) ; 
 struct commit* prio_queue_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct commit *next_topo_commit(struct rev_info *revs)
{
	struct commit *c;
	struct topo_walk_info *info = revs->topo_walk_info;

	/* pop next off of topo_queue */
	c = prio_queue_get(&info->topo_queue);

	if (c)
		*(indegree_slab_at(&info->indegree, c)) = 0;

	return c;
}