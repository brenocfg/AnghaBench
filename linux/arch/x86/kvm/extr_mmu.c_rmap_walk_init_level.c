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
struct slot_rmap_walk_iterator {int level; int /*<<< orphan*/  slot; int /*<<< orphan*/  end_gfn; void* end_rmap; int /*<<< orphan*/  gfn; void* rmap; int /*<<< orphan*/  start_gfn; } ;

/* Variables and functions */
 void* __gfn_to_rmap (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rmap_walk_init_level(struct slot_rmap_walk_iterator *iterator, int level)
{
	iterator->level = level;
	iterator->gfn = iterator->start_gfn;
	iterator->rmap = __gfn_to_rmap(iterator->gfn, level, iterator->slot);
	iterator->end_rmap = __gfn_to_rmap(iterator->end_gfn, level,
					   iterator->slot);
}