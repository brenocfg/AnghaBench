#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ (* get_order ) (TYPE_2__*,TYPE_2__*) ;int /*<<< orphan*/  no_of_elements; TYPE_2__* front; } ;
typedef  TYPE_1__ queue ;
struct TYPE_8__ {struct TYPE_8__* node_next; } ;
typedef  TYPE_2__ node ;

/* Variables and functions */
 scalar_t__ stub1 (TYPE_2__*,TYPE_2__*) ; 

queue *enqueue(
	queue *	my_queue,
	void *	my_node
	)
{
	node *new_node = (node *)my_node - 1;
	node *i = NULL;
	node *j = my_queue->front;

	while (j != NULL && 
	       (*my_queue->get_order)(new_node + 1, j + 1) > 0) {
		i = j;
		j = j->node_next;
	}

	if (i == NULL) {	/* Insert at beginning of the queue */
		new_node->node_next = my_queue->front;
		my_queue->front = new_node;
	} else {		/* Insert Elsewhere, including the end */
		new_node->node_next = i->node_next;
		i->node_next = new_node;
	}

	++my_queue->no_of_elements;    
	return my_queue;
}