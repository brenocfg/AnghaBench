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
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PRINTK_3 (int /*<<< orphan*/ ,char*,int,void*) ; 
 int /*<<< orphan*/  TRACE_TP3780I ; 

__attribute__((used)) static irqreturn_t UartInterrupt(int irq, void *dev_id)
{
	PRINTK_3(TRACE_TP3780I,
		"tp3780i::UartInterrupt entry irq %x dev_id %p\n", irq, dev_id);
	return IRQ_HANDLED;
}