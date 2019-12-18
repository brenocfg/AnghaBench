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
struct irq_data {unsigned int hwirq; } ;

/* Variables and functions */
 int /*<<< orphan*/  IER ; 
 int /*<<< orphan*/  core_irq_lock ; 
 int /*<<< orphan*/  or_creg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  raw_spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unmask_core_irq(struct irq_data *data)
{
	unsigned int prio = data->hwirq;

	raw_spin_lock(&core_irq_lock);
	or_creg(IER, 1 << prio);
	raw_spin_unlock(&core_irq_lock);
}