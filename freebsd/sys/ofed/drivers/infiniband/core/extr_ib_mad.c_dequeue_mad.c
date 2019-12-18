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
struct ib_mad_queue {int /*<<< orphan*/  lock; int /*<<< orphan*/  count; } ;
struct ib_mad_list_head {int /*<<< orphan*/  list; struct ib_mad_queue* mad_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void dequeue_mad(struct ib_mad_list_head *mad_list)
{
	struct ib_mad_queue *mad_queue;
	unsigned long flags;

	BUG_ON(!mad_list->mad_queue);
	mad_queue = mad_list->mad_queue;
	spin_lock_irqsave(&mad_queue->lock, flags);
	list_del(&mad_list->list);
	mad_queue->count--;
	spin_unlock_irqrestore(&mad_queue->lock, flags);
}