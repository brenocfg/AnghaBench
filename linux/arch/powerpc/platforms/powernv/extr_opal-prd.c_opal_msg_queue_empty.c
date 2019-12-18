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

/* Variables and functions */
 int list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opal_prd_msg_queue ; 
 int /*<<< orphan*/  opal_prd_msg_queue_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static bool opal_msg_queue_empty(void)
{
	unsigned long flags;
	bool ret;

	spin_lock_irqsave(&opal_prd_msg_queue_lock, flags);
	ret = list_empty(&opal_prd_msg_queue);
	spin_unlock_irqrestore(&opal_prd_msg_queue_lock, flags);

	return ret;
}