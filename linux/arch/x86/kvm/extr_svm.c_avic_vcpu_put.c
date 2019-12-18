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
typedef  int u64 ;
struct vcpu_svm {int /*<<< orphan*/ * avic_physical_id_cache; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avic_update_iommu_vcpu_affinity (struct kvm_vcpu*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void avic_vcpu_put(struct kvm_vcpu *vcpu)
{
	u64 entry;
	struct vcpu_svm *svm = to_svm(vcpu);

	if (!kvm_vcpu_apicv_active(vcpu))
		return;

	entry = READ_ONCE(*(svm->avic_physical_id_cache));
	if (entry & AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK)
		avic_update_iommu_vcpu_affinity(vcpu, -1, 0);

	entry &= ~AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK;
	WRITE_ONCE(*(svm->avic_physical_id_cache), entry);
}