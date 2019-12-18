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
typedef  int /*<<< orphan*/  ulong ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_DATA_STORAGE ; 
 int /*<<< orphan*/  kvmppc_inject_interrupt (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_dar (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_set_dsisr (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

void kvmppc_core_queue_data_storage(struct kvm_vcpu *vcpu, ulong dar,
				    ulong flags)
{
	kvmppc_set_dar(vcpu, dar);
	kvmppc_set_dsisr(vcpu, flags);
	kvmppc_inject_interrupt(vcpu, BOOK3S_INTERRUPT_DATA_STORAGE, 0);
}