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
struct kvm_vcpu_hv_synic {int active; int dont_zero_synic_pages; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vcpu_deactivate_apicv (struct kvm_vcpu*) ; 
 struct kvm_vcpu_hv_synic* vcpu_to_synic (struct kvm_vcpu*) ; 

int kvm_hv_activate_synic(struct kvm_vcpu *vcpu, bool dont_zero_synic_pages)
{
	struct kvm_vcpu_hv_synic *synic = vcpu_to_synic(vcpu);

	/*
	 * Hyper-V SynIC auto EOI SINT's are
	 * not compatible with APICV, so deactivate APICV
	 */
	kvm_vcpu_deactivate_apicv(vcpu);
	synic->active = true;
	synic->dont_zero_synic_pages = dont_zero_synic_pages;
	return 0;
}