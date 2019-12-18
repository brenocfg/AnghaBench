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
 int /*<<< orphan*/  CPUHP_AP_ONLINE_IDLE ; 
 int /*<<< orphan*/  Dprintk (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IA64_KR_IO_BASE ; 
 int /*<<< orphan*/  __pa (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_init () ; 
 int /*<<< orphan*/  cpu_startup_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efi_map_pal_code () ; 
 int /*<<< orphan*/  hard_smp_processor_id () ; 
 int /*<<< orphan*/  ia64_iobase ; 
 int /*<<< orphan*/  ia64_set_kr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  smp_callin () ; 

int
start_secondary (void *unused)
{
	/* Early console may use I/O ports */
	ia64_set_kr(IA64_KR_IO_BASE, __pa(ia64_iobase));
#ifndef CONFIG_PRINTK_TIME
	Dprintk("start_secondary: starting CPU 0x%x\n", hard_smp_processor_id());
#endif
	efi_map_pal_code();
	cpu_init();
	preempt_disable();
	smp_callin();

	cpu_startup_entry(CPUHP_AP_ONLINE_IDLE);
	return 0;
}