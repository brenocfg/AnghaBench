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
struct irq_data {int irq; } ;

/* Variables and functions */
 unsigned long cached_irq_mask ; 
 int /*<<< orphan*/  dp264_irq_lock ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsunami_update_irq_hw (unsigned long) ; 

__attribute__((used)) static void
clipper_enable_irq(struct irq_data *d)
{
	spin_lock(&dp264_irq_lock);
	cached_irq_mask |= 1UL << (d->irq - 16);
	tsunami_update_irq_hw(cached_irq_mask);
	spin_unlock(&dp264_irq_lock);
}