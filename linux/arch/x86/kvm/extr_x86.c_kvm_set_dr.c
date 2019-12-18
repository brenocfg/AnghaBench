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

/* Variables and functions */
 scalar_t__ __kvm_set_dr (struct kvm_vcpu*,int,unsigned long) ; 
 int /*<<< orphan*/  kvm_inject_gp (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

int kvm_set_dr(struct kvm_vcpu *vcpu, int dr, unsigned long val)
{
	if (__kvm_set_dr(vcpu, dr, val)) {
		kvm_inject_gp(vcpu, 0);
		return 1;
	}
	return 0;
}