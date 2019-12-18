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
struct kvm_s390_sie_block {int /*<<< orphan*/  cpuflags; } ;
struct vsie_page {struct kvm_s390_sie_block* scb_o; struct kvm_s390_sie_block scb_s; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; } ;

/* Variables and functions */
 int CPUSTAT_GED ; 
 int CPUSTAT_GED2 ; 
 int CPUSTAT_IBS ; 
 int CPUSTAT_KSS ; 
 int CPUSTAT_MCDS ; 
 int CPUSTAT_P ; 
 int CPUSTAT_RRF ; 
 int CPUSTAT_SLSR ; 
 int CPUSTAT_SLSV ; 
 int CPUSTAT_SM ; 
 int CPUSTAT_ZARCH ; 
 int /*<<< orphan*/  KVM_S390_VM_CPU_FEAT_GPERE ; 
 int /*<<< orphan*/  KVM_S390_VM_CPU_FEAT_GSLS ; 
 int /*<<< orphan*/  KVM_S390_VM_CPU_FEAT_IBS ; 
 int /*<<< orphan*/  KVM_S390_VM_CPU_FEAT_KSS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int set_validity_icpt (struct kvm_s390_sie_block*,int) ; 
 scalar_t__ test_kvm_cpu_feat (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_kvm_facility (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prepare_cpuflags(struct kvm_vcpu *vcpu, struct vsie_page *vsie_page)
{
	struct kvm_s390_sie_block *scb_s = &vsie_page->scb_s;
	struct kvm_s390_sie_block *scb_o = vsie_page->scb_o;
	int newflags, cpuflags = atomic_read(&scb_o->cpuflags);

	/* we don't allow ESA/390 guests */
	if (!(cpuflags & CPUSTAT_ZARCH))
		return set_validity_icpt(scb_s, 0x0001U);

	if (cpuflags & (CPUSTAT_RRF | CPUSTAT_MCDS))
		return set_validity_icpt(scb_s, 0x0001U);
	else if (cpuflags & (CPUSTAT_SLSV | CPUSTAT_SLSR))
		return set_validity_icpt(scb_s, 0x0007U);

	/* intervention requests will be set later */
	newflags = CPUSTAT_ZARCH;
	if (cpuflags & CPUSTAT_GED && test_kvm_facility(vcpu->kvm, 8))
		newflags |= CPUSTAT_GED;
	if (cpuflags & CPUSTAT_GED2 && test_kvm_facility(vcpu->kvm, 78)) {
		if (cpuflags & CPUSTAT_GED)
			return set_validity_icpt(scb_s, 0x0001U);
		newflags |= CPUSTAT_GED2;
	}
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_GPERE))
		newflags |= cpuflags & CPUSTAT_P;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_GSLS))
		newflags |= cpuflags & CPUSTAT_SM;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_IBS))
		newflags |= cpuflags & CPUSTAT_IBS;
	if (test_kvm_cpu_feat(vcpu->kvm, KVM_S390_VM_CPU_FEAT_KSS))
		newflags |= cpuflags & CPUSTAT_KSS;

	atomic_set(&scb_s->cpuflags, newflags);
	return 0;
}