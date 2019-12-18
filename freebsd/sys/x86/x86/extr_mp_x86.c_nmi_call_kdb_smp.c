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
typedef  int /*<<< orphan*/  u_int ;
struct trapframe {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET_ATOMIC (int,int /*<<< orphan*/ *) ; 
 int PCPU_GET (int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_cmpset_acq_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  atomic_store_rel_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid ; 
 int /*<<< orphan*/  cpustop_handler_post (int) ; 
 int /*<<< orphan*/  ia32_pause () ; 
 int /*<<< orphan*/  nmi_call_kdb (int,int /*<<< orphan*/ ,struct trapframe*) ; 
 int /*<<< orphan*/  nmi_kdb_lock ; 
 int /*<<< orphan*/  savectx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * stoppcbs ; 
 int /*<<< orphan*/  stopped_cpus ; 

void
nmi_call_kdb_smp(u_int type, struct trapframe *frame)
{
	int cpu;
	bool call_post;

	cpu = PCPU_GET(cpuid);
	if (atomic_cmpset_acq_int(&nmi_kdb_lock, 0, 1)) {
		nmi_call_kdb(cpu, type, frame);
		call_post = false;
	} else {
		savectx(&stoppcbs[cpu]);
		CPU_SET_ATOMIC(cpu, &stopped_cpus);
		while (!atomic_cmpset_acq_int(&nmi_kdb_lock, 0, 1))
			ia32_pause();
		call_post = true;
	}
	atomic_store_rel_int(&nmi_kdb_lock, 0);
	if (call_post)
		cpustop_handler_post(cpu);
}