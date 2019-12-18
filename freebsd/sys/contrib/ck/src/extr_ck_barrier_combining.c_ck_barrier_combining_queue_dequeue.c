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
struct ck_barrier_combining_queue {struct ck_barrier_combining_group* head; } ;
struct ck_barrier_combining_group {struct ck_barrier_combining_group* next; } ;

/* Variables and functions */

__attribute__((used)) static struct ck_barrier_combining_group *
ck_barrier_combining_queue_dequeue(struct ck_barrier_combining_queue *queue)
{
	struct ck_barrier_combining_group *front = NULL;

	if (queue->head != NULL) {
		front = queue->head;
		queue->head = queue->head->next;
	}

	return front;
}