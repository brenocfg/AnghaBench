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
typedef  scalar_t__ u64 ;
struct kvm_vcpu {int dummy; } ;
typedef  int /*<<< orphan*/  gpa_t ;

/* Variables and functions */
 scalar_t__ is_pae (struct kvm_vcpu*) ; 
 int kvm_vcpu_read_guest_atomic (struct kvm_vcpu*,int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static u64 mmu_pte_write_fetch_gpte(struct kvm_vcpu *vcpu, gpa_t *gpa,
				    int *bytes)
{
	u64 gentry = 0;
	int r;

	/*
	 * Assume that the pte write on a page table of the same type
	 * as the current vcpu paging mode since we update the sptes only
	 * when they have the same mode.
	 */
	if (is_pae(vcpu) && *bytes == 4) {
		/* Handle a 32-bit guest writing two halves of a 64-bit gpte */
		*gpa &= ~(gpa_t)7;
		*bytes = 8;
	}

	if (*bytes == 4 || *bytes == 8) {
		r = kvm_vcpu_read_guest_atomic(vcpu, *gpa, &gentry, *bytes);
		if (r)
			gentry = 0;
	}

	return gentry;
}