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
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  irq_err_count ; 
 int /*<<< orphan*/  printk (char*,unsigned int) ; 

void ack_bad_irq(unsigned int irq)
{
	atomic_inc(&irq_err_count);
	printk("unexpected IRQ trap at vector %02x\n", irq);
}