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
struct TYPE_2__ {int /*<<< orphan*/  direct; } ;
struct kvm_mmu_page {scalar_t__ gfns; TYPE_1__ role; scalar_t__ spt; int /*<<< orphan*/  link; int /*<<< orphan*/  hash_link; } ;

/* Variables and functions */
 int /*<<< orphan*/  MMU_WARN_ON (int) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_empty_shadow_page (scalar_t__) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct kvm_mmu_page*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_page_header_cache ; 

__attribute__((used)) static void kvm_mmu_free_page(struct kvm_mmu_page *sp)
{
	MMU_WARN_ON(!is_empty_shadow_page(sp->spt));
	hlist_del(&sp->hash_link);
	list_del(&sp->link);
	free_page((unsigned long)sp->spt);
	if (!sp->role.direct)
		free_page((unsigned long)sp->gfns);
	kmem_cache_free(mmu_page_header_cache, sp);
}