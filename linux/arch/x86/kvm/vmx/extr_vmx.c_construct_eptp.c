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
typedef  unsigned long u64 ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_MASK ; 
 unsigned long VMX_EPTP_AD_ENABLE_BIT ; 
 unsigned long VMX_EPTP_MT_WB ; 
 unsigned long VMX_EPTP_PWL_4 ; 
 unsigned long VMX_EPTP_PWL_5 ; 
 scalar_t__ enable_ept_ad_bits ; 
 int get_ept_level (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ nested_ept_ad_enabled (struct kvm_vcpu*) ; 

u64 construct_eptp(struct kvm_vcpu *vcpu, unsigned long root_hpa)
{
	u64 eptp = VMX_EPTP_MT_WB;

	eptp |= (get_ept_level(vcpu) == 5) ? VMX_EPTP_PWL_5 : VMX_EPTP_PWL_4;

	if (enable_ept_ad_bits &&
	    (!is_guest_mode(vcpu) || nested_ept_ad_enabled(vcpu)))
		eptp |= VMX_EPTP_AD_ENABLE_BIT;
	eptp |= (root_hpa & PAGE_MASK);

	return eptp;
}