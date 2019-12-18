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
struct ena_com_admin_queue {int /*<<< orphan*/  q_lock; int /*<<< orphan*/  outstanding_cmds; } ;
struct ena_com_dev {struct ena_com_admin_queue admin_queue; } ;

/* Variables and functions */
 scalar_t__ ATOMIC32_READ (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ENA_MSLEEP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENA_POLL_MS ; 
 int /*<<< orphan*/  ENA_SPINLOCK_LOCK (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ENA_SPINLOCK_UNLOCK (int /*<<< orphan*/ ,unsigned long) ; 

void ena_com_wait_for_abort_completion(struct ena_com_dev *ena_dev)
{
	struct ena_com_admin_queue *admin_queue = &ena_dev->admin_queue;
	unsigned long flags = 0;

	ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
	while (ATOMIC32_READ(&admin_queue->outstanding_cmds) != 0) {
		ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);
		ENA_MSLEEP(ENA_POLL_MS);
		ENA_SPINLOCK_LOCK(admin_queue->q_lock, flags);
	}
	ENA_SPINLOCK_UNLOCK(admin_queue->q_lock, flags);
}