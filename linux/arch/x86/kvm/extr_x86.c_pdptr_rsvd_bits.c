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
 int cpuid_maxphyaddr (struct kvm_vcpu*) ; 
 int rsvd_bits (int,int) ; 

__attribute__((used)) static inline u64 pdptr_rsvd_bits(struct kvm_vcpu *vcpu)
{
	return rsvd_bits(cpuid_maxphyaddr(vcpu), 63) | rsvd_bits(5, 8) |
	       rsvd_bits(1, 2);
}