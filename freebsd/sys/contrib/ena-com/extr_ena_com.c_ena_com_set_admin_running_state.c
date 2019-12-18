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
struct ena_com_admin_queue {int running_state; int /*<<< orphan*/  q_lock; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENA_SPINLOCK_LOCK (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ENA_SPINLOCK_UNLOCK (int /*<<< orphan*/ ,unsigned long) ; 

void ena_com_set_admin_running_state(struct ena_com_dev *ena_dev, bool state)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	unsigned long flags = 0;

	ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
	ena_dev->admin_queue.running_state = state;
	ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);
}