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
struct pack_list {scalar_t__ all_objects_size; TYPE_1__* remaining_objects; } ;
struct TYPE_2__ {scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_remaining_objects(const void *a, const void *b)
{
	struct pack_list *pl_a = *((struct pack_list **)a);
	struct pack_list *pl_b = *((struct pack_list **)b);

	if (pl_a->remaining_objects->size == pl_b->remaining_objects->size) {
		/* have the same remaining_objects, big pack first */
		if (pl_a->all_objects_size == pl_b->all_objects_size)
			return 0;
		else if (pl_a->all_objects_size < pl_b->all_objects_size)
			return 1;
		else
			return -1;
	} else if (pl_a->remaining_objects->size < pl_b->remaining_objects->size) {
		/* sort by remaining objects, more objects first */
		return 1;
	} else {
		return -1;
	}
}