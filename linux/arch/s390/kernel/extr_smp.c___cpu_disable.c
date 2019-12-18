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
 int /*<<< orphan*/  CIF_NOHZ_DELAY ; 
 int /*<<< orphan*/  __ctl_load (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  __ctl_store (unsigned long*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_cpu_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pfault_fini () ; 
 int /*<<< orphan*/  set_cpu_online (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smp_handle_ext_call () ; 
 int /*<<< orphan*/  smp_processor_id () ; 

int __cpu_disable(void)
{
	unsigned long cregs[16];

	/* Handle possible pending IPIs */
	smp_handle_ext_call();
	set_cpu_online(smp_processor_id(), false);
	/* Disable pseudo page faults on this cpu. */
	pfault_fini();
	/* Disable interrupt sources via control register. */
	__ctl_store(cregs, 0, 15);
	cregs[0]  &= ~0x0000ee70UL;	/* disable all external interrupts */
	cregs[6]  &= ~0xff000000UL;	/* disable all I/O interrupts */
	cregs[14] &= ~0x1f000000UL;	/* disable most machine checks */
	__ctl_load(cregs, 0, 15);
	clear_cpu_flag(CIF_NOHZ_DELAY);
	return 0;
}