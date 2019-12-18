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
struct sun4d_handler_data {int cpuid; unsigned int real_irq; } ;
struct irq_data {int dummy; } ;

/* Variables and functions */
 int cc_get_imsk () ; 
 int cc_get_imsk_other (int) ; 
 int /*<<< orphan*/  cc_set_imsk (int) ; 
 int /*<<< orphan*/  cc_set_imsk_other (int,int) ; 
 struct sun4d_handler_data* irq_data_get_irq_handler_data (struct irq_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  sun4d_imsk_lock ; 

__attribute__((used)) static void sun4d_mask_irq(struct irq_data *data)
{
	struct sun4d_handler_data *handler_data = irq_data_get_irq_handler_data(data);
	unsigned int real_irq;
#ifdef CONFIG_SMP
	int cpuid = handler_data->cpuid;
	unsigned long flags;
#endif
	real_irq = handler_data->real_irq;
#ifdef CONFIG_SMP
	spin_lock_irqsave(&sun4d_imsk_lock, flags);
	cc_set_imsk_other(cpuid, cc_get_imsk_other(cpuid) | (1 << real_irq));
	spin_unlock_irqrestore(&sun4d_imsk_lock, flags);
#else
	cc_set_imsk(cc_get_imsk() | (1 << real_irq));
#endif
}