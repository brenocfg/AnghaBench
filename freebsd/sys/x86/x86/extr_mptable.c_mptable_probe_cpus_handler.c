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
typedef  int u_char ;
typedef  TYPE_1__* proc_entry_ptr ;
struct TYPE_2__ {int cpu_flags; int /*<<< orphan*/  apic_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAXCPU ; 
 int /*<<< orphan*/  MAX_LAPIC_ID ; 
#define  MPCT_ENTRY_PROCESSOR 128 
 int PROCENTRY_FLAG_EN ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max_apic_id ; 
 int /*<<< orphan*/  mp_maxid ; 
 int /*<<< orphan*/  mp_ncpus ; 

__attribute__((used)) static void
mptable_probe_cpus_handler(u_char *entry, void *arg)
{
	proc_entry_ptr proc;

	switch (*entry) {
	case MPCT_ENTRY_PROCESSOR:
		proc = (proc_entry_ptr)entry;
		if (proc->cpu_flags & PROCENTRY_FLAG_EN &&
		    proc->apic_id < MAX_LAPIC_ID && mp_ncpus < MAXCPU) {
#ifdef SMP
			mp_ncpus++;
			mp_maxid = mp_ncpus - 1;
#endif
			max_apic_id = max(max_apic_id, proc->apic_id);
		}
		break;
	}
}