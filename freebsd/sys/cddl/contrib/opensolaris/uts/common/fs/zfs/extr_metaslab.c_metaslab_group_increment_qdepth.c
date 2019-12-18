#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {scalar_t__ mg_max_alloc_queue_depth; scalar_t__* mg_cur_max_alloc_queue_depth; TYPE_1__* mg_class; } ;
typedef  TYPE_2__ metaslab_group_t ;
struct TYPE_4__ {int /*<<< orphan*/ * mc_alloc_max_slots; } ;

/* Variables and functions */
 scalar_t__ atomic_cas_64 (scalar_t__*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  atomic_inc_64 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
metaslab_group_increment_qdepth(metaslab_group_t *mg, int allocator)
{
	uint64_t max = mg->mg_max_alloc_queue_depth;
	uint64_t cur = mg->mg_cur_max_alloc_queue_depth[allocator];
	while (cur < max) {
		if (atomic_cas_64(&mg->mg_cur_max_alloc_queue_depth[allocator],
		    cur, cur + 1) == cur) {
			atomic_inc_64(
			    &mg->mg_class->mc_alloc_max_slots[allocator]);
			return;
		}
		cur = mg->mg_cur_max_alloc_queue_depth[allocator];
	}
}