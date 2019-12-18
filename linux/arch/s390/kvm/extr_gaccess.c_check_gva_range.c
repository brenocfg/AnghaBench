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
typedef  int /*<<< orphan*/  u8 ;
struct kvm_vcpu {int dummy; } ;
typedef  enum gacc_mode { ____Placeholder_gacc_mode } gacc_mode ;

/* Variables and functions */
 unsigned long PAGE_SIZE ; 
 int guest_translate_address (struct kvm_vcpu*,unsigned long,int /*<<< orphan*/ ,unsigned long*,int) ; 
 int /*<<< orphan*/  ipte_lock (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  ipte_unlock (struct kvm_vcpu*) ; 
 unsigned long min (unsigned long,unsigned long) ; 

int check_gva_range(struct kvm_vcpu *vcpu, unsigned long gva, u8 ar,
		    unsigned long length, enum gacc_mode mode)
{
	unsigned long gpa;
	unsigned long currlen;
	int rc = 0;

	ipte_lock(vcpu);
	while (length > 0 && !rc) {
		currlen = min(length, PAGE_SIZE - (gva % PAGE_SIZE));
		rc = guest_translate_address(vcpu, gva, ar, &gpa, mode);
		gva += currlen;
		length -= currlen;
	}
	ipte_unlock(vcpu);

	return rc;
}