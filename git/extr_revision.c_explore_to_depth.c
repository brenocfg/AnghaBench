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
typedef  scalar_t__ uint32_t ;
struct topo_walk_info {int /*<<< orphan*/  explore_queue; } ;
struct rev_info {struct topo_walk_info* topo_walk_info; } ;
struct commit {scalar_t__ generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  explore_walk_step (struct rev_info*) ; 
 struct commit* prio_queue_peek (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void explore_to_depth(struct rev_info *revs,
			     uint32_t gen_cutoff)
{
	struct topo_walk_info *info = revs->topo_walk_info;
	struct commit *c;
	while ((c = prio_queue_peek(&info->explore_queue)) &&
	       c->generation >= gen_cutoff)
		explore_walk_step(revs);
}