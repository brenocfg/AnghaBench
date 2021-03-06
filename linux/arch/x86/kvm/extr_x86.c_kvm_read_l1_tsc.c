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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ (* read_l1_tsc_offset ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 scalar_t__ kvm_scale_tsc (struct kvm_vcpu*,scalar_t__) ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

u64 kvm_read_l1_tsc(struct kvm_vcpu *vcpu, u64 host_tsc)
{
	u64 tsc_offset = kvm_x86_ops->read_l1_tsc_offset(vcpu);

	return tsc_offset + kvm_scale_tsc(vcpu, host_tsc);
}