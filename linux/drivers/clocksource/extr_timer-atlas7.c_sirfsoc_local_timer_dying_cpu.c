#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  remove_irq (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__ sirfsoc_timer1_irq ; 
 int /*<<< orphan*/  sirfsoc_timer_count_disable (int) ; 
 TYPE_1__ sirfsoc_timer_irq ; 

__attribute__((used)) static int sirfsoc_local_timer_dying_cpu(unsigned int cpu)
{
	sirfsoc_timer_count_disable(1);

	if (cpu == 0)
		remove_irq(sirfsoc_timer_irq.irq, &sirfsoc_timer_irq);
	else
		remove_irq(sirfsoc_timer1_irq.irq, &sirfsoc_timer1_irq);
	return 0;
}