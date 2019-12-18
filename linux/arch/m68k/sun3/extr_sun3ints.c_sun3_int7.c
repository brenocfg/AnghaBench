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
 unsigned int kstat_irqs_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * led_pattern ; 
 int /*<<< orphan*/  sun3_leds (int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t sun3_int7(int irq, void *dev_id)
{
	unsigned int cnt;

	cnt = kstat_irqs_cpu(irq, 0);
	if (!(cnt % 2000))
		sun3_leds(led_pattern[cnt % 16000 / 2000]);
	return IRQ_HANDLED;
}