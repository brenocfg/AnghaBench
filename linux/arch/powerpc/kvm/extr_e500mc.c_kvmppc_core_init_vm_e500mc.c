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
struct TYPE_2__ {int lpid; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int kvmppc_alloc_lpid () ; 
 int threads_per_core ; 

__attribute__((used)) static int kvmppc_core_init_vm_e500mc(struct kvm *kvm)
{
	int lpid;

	lpid = kvmppc_alloc_lpid();
	if (lpid < 0)
		return lpid;

	/*
	 * Use two lpids per VM on cores with two threads like e6500. Use
	 * even numbers to speedup vcpu lpid computation with consecutive lpids
	 * per VM. vm1 will use lpids 2 and 3, vm2 lpids 4 and 5, and so on.
	 */
	if (threads_per_core == 2)
		lpid <<= 1;

	kvm->arch.lpid = lpid;
	return 0;
}