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
struct TYPE_2__ {int hwthread_req; scalar_t__ hwthread_state; scalar_t__ napping; int /*<<< orphan*/ * kvm_vcore; int /*<<< orphan*/ * kvm_vcpu; } ;
struct paca_struct {TYPE_1__ kvm_hstate; } ;

/* Variables and functions */
 int EBUSY ; 
 scalar_t__ KVM_HWTHREAD_IN_KERNEL ; 
 struct paca_struct** paca_ptrs ; 
 int /*<<< orphan*/  pr_err (char*,int) ; 
 int /*<<< orphan*/  smp_mb () ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int kvmppc_grab_hwthread(int cpu)
{
	struct paca_struct *tpaca;
	long timeout = 10000;

	tpaca = paca_ptrs[cpu];

	/* Ensure the thread won't go into the kernel if it wakes */
	tpaca->kvm_hstate.kvm_vcpu = NULL;
	tpaca->kvm_hstate.kvm_vcore = NULL;
	tpaca->kvm_hstate.napping = 0;
	smp_wmb();
	tpaca->kvm_hstate.hwthread_req = 1;

	/*
	 * If the thread is already executing in the kernel (e.g. handling
	 * a stray interrupt), wait for it to get back to nap mode.
	 * The smp_mb() is to ensure that our setting of hwthread_req
	 * is visible before we look at hwthread_state, so if this
	 * races with the code at system_reset_pSeries and the thread
	 * misses our setting of hwthread_req, we are sure to see its
	 * setting of hwthread_state, and vice versa.
	 */
	smp_mb();
	while (tpaca->kvm_hstate.hwthread_state == KVM_HWTHREAD_IN_KERNEL) {
		if (--timeout <= 0) {
			pr_err("KVM: couldn't grab cpu %d\n", cpu);
			return -EBUSY;
		}
		udelay(1);
	}
	return 0;
}