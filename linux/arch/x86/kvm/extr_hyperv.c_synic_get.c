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
typedef  int /*<<< orphan*/  u32 ;
struct kvm_vcpu_hv_synic {scalar_t__ active; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 struct kvm_vcpu* get_vcpu_by_vpidx (struct kvm*,int /*<<< orphan*/ ) ; 
 struct kvm_vcpu_hv_synic* vcpu_to_synic (struct kvm_vcpu*) ; 

__attribute__((used)) static struct kvm_vcpu_hv_synic *synic_get(struct kvm *kvm, u32 vpidx)
{
	struct kvm_vcpu *vcpu;
	struct kvm_vcpu_hv_synic *synic;

	vcpu = get_vcpu_by_vpidx(kvm, vpidx);
	if (!vcpu)
		return NULL;
	synic = vcpu_to_synic(vcpu);
	return (synic->active) ? synic : NULL;
}