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
struct prio_queue {int nr; TYPE_1__* array; int /*<<< orphan*/  compare; } ;
struct TYPE_2__ {void* data; } ;

/* Variables and functions */

void *prio_queue_peek(struct prio_queue *queue)
{
	if (!queue->nr)
		return NULL;
	if (!queue->compare)
		return queue->array[queue->nr - 1].data;
	return queue->array[0].data;
}