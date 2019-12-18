#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct camq {size_t entries; size_t array_size; TYPE_1__** queue_array; } ;
struct TYPE_4__ {size_t index; } ;
typedef  TYPE_1__ cam_pinfo ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  heap_up (TYPE_1__**,size_t) ; 

void
camq_insert(struct camq *queue, cam_pinfo *new_entry)
{

	KASSERT(queue->entries < queue->array_size,
	    ("camq_insert: Attempt to insert into a full queue (%d >= %d)",
	    queue->entries, queue->array_size));
	queue->entries++;
	queue->queue_array[queue->entries] = new_entry;
	new_entry->index = queue->entries;
	if (queue->entries != 0)
		heap_up(queue->queue_array, queue->entries);
}