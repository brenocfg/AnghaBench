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
struct vcpu_svm {scalar_t__ avic_is_running; int /*<<< orphan*/ * avic_physical_id_cache; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK ; 
 int AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  avic_update_iommu_vcpu_affinity (struct kvm_vcpu*,int,scalar_t__) ; 
 int kvm_cpu_get_apicid (int) ; 
 int /*<<< orphan*/  kvm_vcpu_apicv_active (struct kvm_vcpu*) ; 
 struct vcpu_svm* to_svm (struct kvm_vcpu*) ; 

__attribute__((used)) static void avic_vcpu_load(struct kvm_vcpu *vcpu, int cpu)
{
	u64 entry;
	/* ID = 0xff (broadcast), ID > 0xff (reserved) */
	int h_physical_id = kvm_cpu_get_apicid(cpu);
	struct vcpu_svm *svm = to_svm(vcpu);

	if (!kvm_vcpu_apicv_active(vcpu))
		return;

	/*
	 * Since the host physical APIC id is 8 bits,
	 * we can support host APIC ID upto 255.
	 */
	if (WARN_ON(h_physical_id > AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK))
		return;

	entry = READ_ONCE(*(svm->avic_physical_id_cache));
	WARN_ON(entry & AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK);

	entry &= ~AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK;
	entry |= (h_physical_id & AVIC_PHYSICAL_ID_ENTRY_HOST_PHYSICAL_ID_MASK);

	entry &= ~AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK;
	if (svm->avic_is_running)
		entry |= AVIC_PHYSICAL_ID_ENTRY_IS_RUNNING_MASK;

	WRITE_ONCE(*(svm->avic_physical_id_cache), entry);
	avic_update_iommu_vcpu_affinity(vcpu, h_physical_id,
					svm->avic_is_running);
}