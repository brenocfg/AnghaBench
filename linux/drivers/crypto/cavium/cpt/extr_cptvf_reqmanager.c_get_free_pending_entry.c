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
struct pending_queue {size_t rear; struct pending_entry* head; } ;
struct pending_entry {int busy; } ;

/* Variables and functions */
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct pending_entry *get_free_pending_entry(struct pending_queue *q,
						    int qlen)
{
	struct pending_entry *ent = NULL;

	ent = &q->head[q->rear];
	if (unlikely(ent->busy)) {
		ent = NULL;
		goto no_free_entry;
	}

	q->rear++;
	if (unlikely(q->rear == qlen))
		q->rear = 0;

no_free_entry:
	return ent;
}