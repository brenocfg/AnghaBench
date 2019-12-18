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
typedef  void* u64 ;
struct kvm_tlb_range {void* pages; void* start_gfn; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  kvm_flush_remote_tlbs_with_range (struct kvm*,struct kvm_tlb_range*) ; 

__attribute__((used)) static void kvm_flush_remote_tlbs_with_address(struct kvm *kvm,
		u64 start_gfn, u64 pages)
{
	struct kvm_tlb_range range;

	range.start_gfn = start_gfn;
	range.pages = pages;

	kvm_flush_remote_tlbs_with_range(kvm, &range);
}