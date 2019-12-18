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
typedef  unsigned long u_int ;
typedef  int u_char ;
typedef  TYPE_1__* proc_entry_ptr ;
struct TYPE_2__ {int cpu_flags; unsigned long apic_id; } ;

/* Variables and functions */
 unsigned long MAX_LAPIC_ID ; 
#define  MPCT_ENTRY_PROCESSOR 128 
 int PROCENTRY_FLAG_BP ; 
 int PROCENTRY_FLAG_EN ; 
 int /*<<< orphan*/  lapic_create (unsigned long,int) ; 

__attribute__((used)) static void
mptable_setup_cpus_handler(u_char *entry, void *arg)
{
	proc_entry_ptr proc;
	u_int *cpu_mask;

	switch (*entry) {
	case MPCT_ENTRY_PROCESSOR:
		proc = (proc_entry_ptr)entry;
		if (proc->cpu_flags & PROCENTRY_FLAG_EN) {
			lapic_create(proc->apic_id, proc->cpu_flags &
			    PROCENTRY_FLAG_BP);
			if (proc->apic_id < MAX_LAPIC_ID) {
				cpu_mask = (u_int *)arg;
				*cpu_mask |= (1ul << proc->apic_id);
			}
		}
		break;
	}
}