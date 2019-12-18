#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct TYPE_2__ {scalar_t__ enlightened_vmcs_enabled; } ;
struct vcpu_vmx {TYPE_1__ nested; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int KVM_EVMCS_VERSION ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

uint16_t nested_get_evmcs_version(struct kvm_vcpu *vcpu)
{
       struct vcpu_vmx *vmx = to_vmx(vcpu);
       /*
        * vmcs_version represents the range of supported Enlightened VMCS
        * versions: lower 8 bits is the minimal version, higher 8 bits is the
        * maximum supported version. KVM supports versions from 1 to
        * KVM_EVMCS_VERSION.
        */
       if (vmx->nested.enlightened_vmcs_enabled)
               return (KVM_EVMCS_VERSION << 8) | 1;

       return 0;
}