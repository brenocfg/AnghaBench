#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* action; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* fn ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  __arch_local_irq_stosm (int) ; 
 int /*<<< orphan*/  crash_kexec (int /*<<< orphan*/ *) ; 
 TYPE_2__ on_restart_trigger ; 
 int /*<<< orphan*/  smp_send_stop () ; 
 int /*<<< orphan*/  stop_run (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void __do_restart(void *ignore)
{
	__arch_local_irq_stosm(0x04); /* enable DAT */
	smp_send_stop();
#ifdef CONFIG_CRASH_DUMP
	crash_kexec(NULL);
#endif
	on_restart_trigger.action->fn(&on_restart_trigger);
	stop_run(&on_restart_trigger);
}