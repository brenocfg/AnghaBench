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
 int /*<<< orphan*/  __this_cpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  paravirt_get_lazy_mode () ; 
 int /*<<< orphan*/  trace_xen_mc_batch (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_mc_irq_flags ; 

__attribute__((used)) static inline void xen_mc_batch(void)
{
	unsigned long flags;

	/* need to disable interrupts until this entry is complete */
	local_irq_save(flags);
	trace_xen_mc_batch(paravirt_get_lazy_mode());
	__this_cpu_write(xen_mc_irq_flags, flags);
}