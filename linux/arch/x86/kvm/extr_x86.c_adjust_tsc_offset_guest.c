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
typedef  scalar_t__ s64 ;
struct TYPE_2__ {scalar_t__ (* read_l1_tsc_offset ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_vcpu_write_tsc_offset (struct kvm_vcpu*,scalar_t__) ; 
 TYPE_1__* kvm_x86_ops ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 

__attribute__((used)) static inline void adjust_tsc_offset_guest(struct kvm_vcpu *vcpu,
					   s64 adjustment)
{
	u64 tsc_offset = kvm_x86_ops->read_l1_tsc_offset(vcpu);
	kvm_vcpu_write_tsc_offset(vcpu, tsc_offset + adjustment);
}