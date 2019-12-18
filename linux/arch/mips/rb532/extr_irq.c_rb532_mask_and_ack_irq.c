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
struct irq_data {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  ack_local_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  group_to_ip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_to_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb532_disable_irq (struct irq_data*) ; 

__attribute__((used)) static void rb532_mask_and_ack_irq(struct irq_data *d)
{
	rb532_disable_irq(d);
	ack_local_irq(group_to_ip(irq_to_group(d->irq)));
}