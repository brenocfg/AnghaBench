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
struct prio_queue {size_t nr; TYPE_1__* array; int /*<<< orphan*/  compare; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */
 scalar_t__ compare (struct prio_queue*,int,int) ; 
 int /*<<< orphan*/  swap (struct prio_queue*,int,int) ; 

void *prio_queue_get(struct prio_queue *queue)
{
	void *result;
	int ix, child;

	if (!queue->nr)
		return NULL;
	if (!queue->compare)
		return queue->array[--queue->nr].data; /* LIFO */

	result = queue->array[0].data;
	if (!--queue->nr)
		return result;

	queue->array[0] = queue->array[queue->nr];

	/* Push down the one at the root */
	for (ix = 0; ix * 2 + 1 < queue->nr; ix = child) {
		child = ix * 2 + 1; /* left */
		if (child + 1 < queue->nr &&
		    compare(queue, child, child + 1) >= 0)
			child++; /* use right child */

		if (compare(queue, ix, child) <= 0)
			break;

		swap(queue, child, ix);
	}
	return result;
}