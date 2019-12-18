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
struct request_queue {int /*<<< orphan*/  queue_lock; int /*<<< orphan*/  icq_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ioc_clear_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  icq_list ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

void ioc_clear_queue(struct request_queue *q)
{
	LIST_HEAD(icq_list);

	spin_lock_irq(&q->queue_lock);
	list_splice_init(&q->icq_list, &icq_list);
	spin_unlock_irq(&q->queue_lock);

	__ioc_clear_queue(&icq_list);
}