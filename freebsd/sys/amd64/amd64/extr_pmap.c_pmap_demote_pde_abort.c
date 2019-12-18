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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct spglist {int dummy; } ;
struct rwlock {int dummy; } ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KTR_PMAP ; 
 int /*<<< orphan*/  SLIST_INIT (struct spglist*) ; 
 int pmap_global_bit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pmap_invalidate_pde_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pmap_remove_pde (int /*<<< orphan*/ ,int*,int /*<<< orphan*/ ,struct spglist*,struct rwlock**) ; 
 int /*<<< orphan*/  trunc_2mpage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_free_pages_toq (struct spglist*,int) ; 

__attribute__((used)) static void
pmap_demote_pde_abort(pmap_t pmap, vm_offset_t va, pd_entry_t *pde,
    pd_entry_t oldpde, struct rwlock **lockp)
{
	struct spglist free;
	vm_offset_t sva;

	SLIST_INIT(&free);
	sva = trunc_2mpage(va);
	pmap_remove_pde(pmap, pde, sva, &free, lockp);
	if ((oldpde & pmap_global_bit(pmap)) == 0)
		pmap_invalidate_pde_page(pmap, sva, oldpde);
	vm_page_free_pages_toq(&free, true);
	CTR2(KTR_PMAP, "pmap_demote_pde: failure for va %#lx in pmap %p",
	    va, pmap);
}