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
typedef  int u32 ;
struct irq_data {int /*<<< orphan*/  hwirq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IDU_M_TRIG_EDGE ; 
 int /*<<< orphan*/  IDU_M_TRIG_LEVEL ; 
 int IRQ_TYPE_EDGE_RISING ; 
 int IRQ_TYPE_LEVEL_HIGH ; 
 int /*<<< orphan*/  idu_set_mode (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcip_lock ; 
 int /*<<< orphan*/  raw_spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  raw_spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int idu_irq_set_type(struct irq_data *data, u32 type)
{
	unsigned long flags;

	/*
	 * ARCv2 IDU HW does not support inverse polarity, so these are the
	 * only interrupt types supported.
	 */
	if (type & ~(IRQ_TYPE_EDGE_RISING | IRQ_TYPE_LEVEL_HIGH))
		return -EINVAL;

	raw_spin_lock_irqsave(&mcip_lock, flags);

	idu_set_mode(data->hwirq, true,
		     type & IRQ_TYPE_EDGE_RISING ? IDU_M_TRIG_EDGE :
						   IDU_M_TRIG_LEVEL,
		     false, 0);

	raw_spin_unlock_irqrestore(&mcip_lock, flags);

	return 0;
}