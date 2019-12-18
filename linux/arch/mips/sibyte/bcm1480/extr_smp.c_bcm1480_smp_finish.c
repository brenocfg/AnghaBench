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
 int /*<<< orphan*/  local_irq_enable () ; 

__attribute__((used)) static void bcm1480_smp_finish(void)
{
	extern void sb1480_clockevent_init(void);

	sb1480_clockevent_init();
	local_irq_enable();
}