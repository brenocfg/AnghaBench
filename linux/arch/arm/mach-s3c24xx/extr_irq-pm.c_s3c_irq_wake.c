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
struct irq_data {int hwirq; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  pr_info (char*,char*,int) ; 
 unsigned long s3c_irqwake_intallow ; 
 unsigned long s3c_irqwake_intmask ; 

int s3c_irq_wake(struct irq_data *data, unsigned int state)
{
	unsigned long irqbit = 1 << data->hwirq;

	if (!(s3c_irqwake_intallow & irqbit))
		return -ENOENT;

	pr_info("wake %s for hwirq %lu\n",
		state ? "enabled" : "disabled", data->hwirq);

	if (!state)
		s3c_irqwake_intmask |= irqbit;
	else
		s3c_irqwake_intmask &= ~irqbit;

	return 0;
}