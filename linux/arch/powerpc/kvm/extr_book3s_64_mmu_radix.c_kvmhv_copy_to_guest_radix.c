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
typedef  int /*<<< orphan*/  gva_t ;

/* Variables and functions */
 long kvmhv_copy_tofrom_guest_radix (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,unsigned long) ; 

long kvmhv_copy_to_guest_radix(struct kvm_vcpu *vcpu, gva_t eaddr, void *from,
			       unsigned long n)
{
	return kvmhv_copy_tofrom_guest_radix(vcpu, eaddr, NULL, from, n);
}