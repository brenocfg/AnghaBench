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
struct TYPE_6__ {int /*<<< orphan*/  tp_value; } ;
struct TYPE_5__ {scalar_t__ mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  __restore_watch (TYPE_1__*) ; 
 int /*<<< orphan*/  cpu_asid (unsigned int,scalar_t__) ; 
 scalar_t__ cpu_has_userlocal ; 
 TYPE_1__* current ; 
 TYPE_2__* current_thread_info () ; 
 int /*<<< orphan*/  restore_dsp (TYPE_1__*) ; 
 unsigned int smp_processor_id () ; 
 int /*<<< orphan*/  write_c0_entryhi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_userlocal (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void mips_cpu_restore(void)
{
	unsigned int cpu = smp_processor_id();

	/* Restore ASID */
	if (current->mm)
		write_c0_entryhi(cpu_asid(cpu, current->mm));

	/* Restore DSP state */
	restore_dsp(current);

	/* Restore UserLocal */
	if (cpu_has_userlocal)
		write_c0_userlocal(current_thread_info()->tp_value);

	/* Restore watch registers */
	__restore_watch(current);
}