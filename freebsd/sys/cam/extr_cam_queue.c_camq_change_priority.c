#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int32_t ;
struct camq {TYPE_1__** queue_array; int /*<<< orphan*/  entries; } ;
struct TYPE_3__ {scalar_t__ priority; } ;

/* Variables and functions */
 int /*<<< orphan*/  heap_down (TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_up (TYPE_1__**,int) ; 

void
camq_change_priority(struct camq *queue, int index, u_int32_t new_priority)
{
	if (new_priority > queue->queue_array[index]->priority) {
		queue->queue_array[index]->priority = new_priority;
		heap_down(queue->queue_array, index, queue->entries);
	} else {
		/* new_priority <= old_priority */
		queue->queue_array[index]->priority = new_priority;
		heap_up(queue->queue_array, index);
	}
}