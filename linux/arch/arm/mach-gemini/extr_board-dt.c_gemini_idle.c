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
 int /*<<< orphan*/  cpu_do_idle () ; 
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static void gemini_idle(void)
{
	/*
	 * Because of broken hardware we have to enable interrupts or the CPU
	 * will never wakeup... Acctualy it is not very good to enable
	 * interrupts first since scheduler can miss a tick, but there is
	 * no other way around this. Platforms that needs it for power saving
	 * should enable it in init code, since by default it is
	 * disabled.
	 */

	/* FIXME: Enabling interrupts here is racy! */
	local_irq_enable();
	cpu_do_idle();
}