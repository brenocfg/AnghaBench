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

/* Variables and functions */
 int __kvmppc_handle_load (struct kvm_run*,struct kvm_vcpu*,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 

int kvmppc_handle_load(struct kvm_run *run, struct kvm_vcpu *vcpu,
		       unsigned int rt, unsigned int bytes,
		       int is_default_endian)
{
	return __kvmppc_handle_load(run, vcpu, rt, bytes, is_default_endian, 0);
}