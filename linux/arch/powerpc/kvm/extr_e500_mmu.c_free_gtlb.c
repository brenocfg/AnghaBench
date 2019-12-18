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
struct kvmppc_vcpu_e500 {int num_shared_tlb_pages; int /*<<< orphan*/ * gtlb_arch; int /*<<< orphan*/ * shared_tlb_pages; int /*<<< orphan*/ ** gtlb_priv; int /*<<< orphan*/ * g2h_tlb1_map; int /*<<< orphan*/  vcpu; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvmppc_core_flush_tlb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 scalar_t__ round_down (uintptr_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_page_dirty_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfree (void*) ; 

__attribute__((used)) static void free_gtlb(struct kvmppc_vcpu_e500 *vcpu_e500)
{
	int i;

	kvmppc_core_flush_tlb(&vcpu_e500->vcpu);
	kfree(vcpu_e500->g2h_tlb1_map);
	kfree(vcpu_e500->gtlb_priv[0]);
	kfree(vcpu_e500->gtlb_priv[1]);

	if (vcpu_e500->shared_tlb_pages) {
		vfree((void *)(round_down((uintptr_t)vcpu_e500->gtlb_arch,
					  PAGE_SIZE)));

		for (i = 0; i < vcpu_e500->num_shared_tlb_pages; i++) {
			set_page_dirty_lock(vcpu_e500->shared_tlb_pages[i]);
			put_page(vcpu_e500->shared_tlb_pages[i]);
		}

		vcpu_e500->num_shared_tlb_pages = 0;

		kfree(vcpu_e500->shared_tlb_pages);
		vcpu_e500->shared_tlb_pages = NULL;
	} else {
		kfree(vcpu_e500->gtlb_arch);
	}

	vcpu_e500->gtlb_arch = NULL;
}