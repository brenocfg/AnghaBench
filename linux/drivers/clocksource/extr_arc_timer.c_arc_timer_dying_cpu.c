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
 int /*<<< orphan*/  arc_timer_irq ; 
 int /*<<< orphan*/  disable_percpu_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int arc_timer_dying_cpu(unsigned int cpu)
{
	disable_percpu_irq(arc_timer_irq);
	return 0;
}