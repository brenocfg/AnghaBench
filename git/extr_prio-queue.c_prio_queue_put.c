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
struct prio_queue {int nr; int /*<<< orphan*/  compare; TYPE_1__* array; int /*<<< orphan*/  insertion_ctr; int /*<<< orphan*/  alloc; } ;
struct TYPE_2__ {void* data; scalar_t__ ctr; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ compare (struct prio_queue*,int,int) ; 
 int /*<<< orphan*/  swap (struct prio_queue*,int,int) ; 

void prio_queue_put(struct prio_queue *queue, void *thing)
{
	int ix, parent;

	/* Append at the end */
	ALLOC_GROW(queue->array, queue->nr + 1, queue->alloc);
	queue->array[queue->nr].ctr = queue->insertion_ctr++;
	queue->array[queue->nr].data = thing;
	queue->nr++;
	if (!queue->compare)
		return; /* LIFO */

	/* Bubble up the new one */
	for (ix = queue->nr - 1; ix; ix = parent) {
		parent = (ix - 1) / 2;
		if (compare(queue, parent, ix) <= 0)
			break;

		swap(queue, parent, ix);
	}
}