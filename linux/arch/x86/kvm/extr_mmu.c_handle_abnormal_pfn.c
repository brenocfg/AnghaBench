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
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  int /*<<< orphan*/  gva_t ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 int /*<<< orphan*/  is_error_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_noslot_pfn (int /*<<< orphan*/ ) ; 
 int kvm_handle_bad_page (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int shadow_mmio_access_mask ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_cache_mmio_info (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static bool handle_abnormal_pfn(struct kvm_vcpu *vcpu, gva_t gva, gfn_t gfn,
				kvm_pfn_t pfn, unsigned access, int *ret_val)
{
	/* The pfn is invalid, report the error! */
	if (unlikely(is_error_pfn(pfn))) {
		*ret_val = kvm_handle_bad_page(vcpu, gfn, pfn);
		return true;
	}

	if (unlikely(is_noslot_pfn(pfn)))
		vcpu_cache_mmio_info(vcpu, gva, gfn,
				     access & shadow_mmio_access_mask);

	return false;
}