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
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  hpa_t ;

/* Variables and functions */
 int /*<<< orphan*/  APIC_ACCESS_ADDR ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_flush_tlb (struct kvm_vcpu*,int) ; 

__attribute__((used)) static void vmx_set_apic_access_page_addr(struct kvm_vcpu *vcpu, hpa_t hpa)
{
	if (!is_guest_mode(vcpu)) {
		vmcs_write64(APIC_ACCESS_ADDR, hpa);
		vmx_flush_tlb(vcpu, true);
	}
}