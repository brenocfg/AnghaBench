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
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int ESR_ELx_ISS_MASK ; 
 int /*<<< orphan*/  HCR_VSE ; 
 int /*<<< orphan*/ * vcpu_hcr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_set_vsesr (struct kvm_vcpu*,int) ; 

void kvm_set_sei_esr(struct kvm_vcpu *vcpu, u64 esr)
{
	vcpu_set_vsesr(vcpu, esr & ESR_ELx_ISS_MASK);
	*vcpu_hcr(vcpu) |= HCR_VSE;
}