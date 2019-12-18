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
typedef  int u64 ;
struct kvm_vcpu {TYPE_2__* kvm; } ;
struct kvm_hv {int hv_crash_ctl; int /*<<< orphan*/ * hv_crash_param; } ;
struct TYPE_3__ {struct kvm_hv hyperv; } ;
struct TYPE_4__ {TYPE_1__ arch; } ;

/* Variables and functions */
 int HV_CRASH_CTL_CRASH_NOTIFY ; 
 int /*<<< orphan*/  KVM_REQ_HV_CRASH ; 
 int /*<<< orphan*/  kvm_make_request (int /*<<< orphan*/ ,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_debug (struct kvm_vcpu*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kvm_hv_msr_set_crash_ctl(struct kvm_vcpu *vcpu, u64 data, bool host)
{
	struct kvm_hv *hv = &vcpu->kvm->arch.hyperv;

	if (host)
		hv->hv_crash_ctl = data & HV_CRASH_CTL_CRASH_NOTIFY;

	if (!host && (data & HV_CRASH_CTL_CRASH_NOTIFY)) {

		vcpu_debug(vcpu, "hv crash (0x%llx 0x%llx 0x%llx 0x%llx 0x%llx)\n",
			  hv->hv_crash_param[0],
			  hv->hv_crash_param[1],
			  hv->hv_crash_param[2],
			  hv->hv_crash_param[3],
			  hv->hv_crash_param[4]);

		/* Send notification about crash to user space */
		kvm_make_request(KVM_REQ_HV_CRASH, vcpu);
	}

	return 0;
}