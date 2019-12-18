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
typedef  unsigned long u64 ;
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 unsigned long H_COPY_PAGE ; 
 unsigned long H_ICACHE_INVALIDATE ; 
 unsigned long H_ICACHE_SYNCHRONIZE ; 
 unsigned long H_PAGE_SET_LOANED ; 
 long H_PARAMETER ; 
 long H_SUCCESS ; 
 long H_TOO_HARD ; 
 unsigned long H_ZERO_PAGE ; 
 unsigned long SZ_4K ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 long kvmppc_do_h_page_init_copy (struct kvm_vcpu*,unsigned long,unsigned long) ; 
 long kvmppc_do_h_page_init_zero (struct kvm_vcpu*,unsigned long) ; 

long kvmppc_rm_h_page_init(struct kvm_vcpu *vcpu, unsigned long flags,
			   unsigned long dest, unsigned long src)
{
	struct kvm *kvm = vcpu->kvm;
	u64 pg_mask = SZ_4K - 1;	/* 4K page size */
	long ret = H_SUCCESS;

	/* Don't handle radix mode here, go up to the virtual mode handler */
	if (kvm_is_radix(kvm))
		return H_TOO_HARD;

	/* Check for invalid flags (H_PAGE_SET_LOANED covers all CMO flags) */
	if (flags & ~(H_ICACHE_INVALIDATE | H_ICACHE_SYNCHRONIZE |
		      H_ZERO_PAGE | H_COPY_PAGE | H_PAGE_SET_LOANED))
		return H_PARAMETER;

	/* dest (and src if copy_page flag set) must be page aligned */
	if ((dest & pg_mask) || ((flags & H_COPY_PAGE) && (src & pg_mask)))
		return H_PARAMETER;

	/* zero and/or copy the page as determined by the flags */
	if (flags & H_COPY_PAGE)
		ret = kvmppc_do_h_page_init_copy(vcpu, dest, src);
	else if (flags & H_ZERO_PAGE)
		ret = kvmppc_do_h_page_init_zero(vcpu, dest);

	/* We can ignore the other flags */

	return ret;
}