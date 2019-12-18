#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  vclock_mode; } ;
struct pvclock_gtod_data {TYPE_1__ clock; } ;
struct kvm_vcpu {TYPE_2__* kvm; int /*<<< orphan*/  vcpu_id; } ;
struct kvm_arch {scalar_t__ nr_vcpus_matched_tsc; scalar_t__ use_master_clock; } ;
struct TYPE_4__ {int /*<<< orphan*/  online_vcpus; struct kvm_arch arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_REQ_MASTERCLOCK_UPDATE ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ gtod_is_based_on_tsc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 struct pvclock_gtod_data pvclock_gtod_data ; 
 int /*<<< orphan*/  trace_kvm_track_tsc (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kvm_track_tsc_matching(struct kvm_vcpu *vcpu)
{
#ifdef CONFIG_X86_64
	bool vcpus_matched;
	struct kvm_arch *ka = &vcpu->kvm->arch;
	struct pvclock_gtod_data *gtod = &pvclock_gtod_data;

	vcpus_matched = (ka->nr_vcpus_matched_tsc + 1 ==
			 atomic_read(&vcpu->kvm->online_vcpus));

	/*
	 * Once the masterclock is enabled, always perform request in
	 * order to update it.
	 *
	 * In order to enable masterclock, the host clocksource must be TSC
	 * and the vcpus need to have matched TSCs.  When that happens,
	 * perform request to enable masterclock.
	 */
	if (ka->use_master_clock ||
	    (gtod_is_based_on_tsc(gtod->clock.vclock_mode) && vcpus_matched))
		kvm_make_request(KVM_REQ_MASTERCLOCK_UPDATE, vcpu);

	trace_kvm_track_tsc(vcpu->vcpu_id, ka->nr_vcpus_matched_tsc,
			    atomic_read(&vcpu->kvm->online_vcpus),
		            ka->use_master_clock, gtod->clock.vclock_mode);
#endif
}