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
 int /*<<< orphan*/  sysctr_timer_enable (int) ; 

__attribute__((used)) static void sysctr_irq_acknowledge(void)
{
	/*
	 * clear the enable bit(EN =0) will clear
	 * the status bit(ISTAT = 0), then the interrupt
	 * signal will be negated(acknowledged).
	 */
	sysctr_timer_enable(false);
}