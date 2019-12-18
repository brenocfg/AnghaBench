#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  (* set_state_shutdown ) (TYPE_1__*) ;} ;
struct timer_of {TYPE_1__ clkevt; } ;

/* Variables and functions */
 int /*<<< orphan*/  disable_irq_nosync (int /*<<< orphan*/ ) ; 
 struct timer_of* per_cpu_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  tegra_to ; 

__attribute__((used)) static int tegra_timer_stop(unsigned int cpu)
{
	struct timer_of *to = per_cpu_ptr(&tegra_to, cpu);

	to->clkevt.set_state_shutdown(&to->clkevt);
	disable_irq_nosync(to->clkevt.irq);

	return 0;
}