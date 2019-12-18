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
struct kimage {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ KEXEC_TYPE_CRASH ; 
 int /*<<< orphan*/  __arch_local_irq_stosm (int) ; 
 int /*<<< orphan*/  __do_machine_kexec (void*) ; 
 int /*<<< orphan*/  __machine_kdump (void*) ; 
 int /*<<< orphan*/  debug_locks_off () ; 
 int /*<<< orphan*/  pfault_fini () ; 
 int /*<<< orphan*/  tracing_off () ; 

__attribute__((used)) static void __machine_kexec(void *data)
{
	__arch_local_irq_stosm(0x04); /* enable DAT */
	pfault_fini();
	tracing_off();
	debug_locks_off();
#ifdef CONFIG_CRASH_DUMP
	if (((struct kimage *) data)->type == KEXEC_TYPE_CRASH)
		__machine_kdump(data);
#endif
	__do_machine_kexec(data);
}