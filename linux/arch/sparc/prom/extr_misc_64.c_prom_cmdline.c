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
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  p1275_cmd_direct (unsigned long*) ; 
 int /*<<< orphan*/  smp_capture () ; 
 int /*<<< orphan*/  smp_release () ; 

void prom_cmdline(void)
{
	unsigned long args[3];
	unsigned long flags;

	local_irq_save(flags);

#ifdef CONFIG_SMP
	smp_capture();
#endif

	args[0] = (unsigned long) "enter";
	args[1] = 0;
	args[2] = 0;

	p1275_cmd_direct(args);

#ifdef CONFIG_SMP
	smp_release();
#endif

	local_irq_restore(flags);
}