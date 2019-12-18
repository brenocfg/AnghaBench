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
typedef  int /*<<< orphan*/  irq_hw_number_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_IDU_SET_MASK ; 
 int /*<<< orphan*/  __mcip_cmd_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mcip_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void idu_irq_mask_raw(irq_hw_number_t hwirq)
{
	unsigned long flags;

	raw_spin_lock_irqsave(&mcip_lock, flags);
	__mcip_cmd_data(CMD_IDU_SET_MASK, hwirq, 1);
	raw_spin_unlock_irqrestore(&mcip_lock, flags);
}