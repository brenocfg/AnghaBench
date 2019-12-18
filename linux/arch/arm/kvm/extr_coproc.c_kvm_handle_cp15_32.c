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
struct kvm_run {int dummy; } ;
struct coproc_params {int dummy; } ;

/* Variables and functions */
 struct coproc_params decode_32bit_hsr (struct kvm_vcpu*) ; 
 int emulate_cp15 (struct kvm_vcpu*,struct coproc_params*) ; 

int kvm_handle_cp15_32(struct kvm_vcpu *vcpu, struct kvm_run *run)
{
	struct coproc_params params = decode_32bit_hsr(vcpu);
	return emulate_cp15(vcpu, &params);
}