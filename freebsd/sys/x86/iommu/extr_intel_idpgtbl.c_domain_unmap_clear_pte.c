#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  uintmax_t ;
struct sf_buf {int dummy; } ;
struct dmar_domain {int /*<<< orphan*/  pgtbl_obj; int /*<<< orphan*/  dmar; } ;
struct TYPE_7__ {int /*<<< orphan*/  pte; } ;
typedef  TYPE_2__ dmar_pte_t ;
typedef  scalar_t__ dmar_gaddr_t ;
struct TYPE_6__ {scalar_t__ ref_count; scalar_t__ pindex; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  dmar_flush_pte_to_ram (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  dmar_pgfree (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  dmar_pte_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmar_unmap_pgtbl (struct sf_buf*) ; 
 int /*<<< orphan*/  domain_free_pgtbl_pde (struct dmar_domain*,scalar_t__,int,int) ; 
 TYPE_1__* sf_buf_page (struct sf_buf*) ; 

__attribute__((used)) static void
domain_unmap_clear_pte(struct dmar_domain *domain, dmar_gaddr_t base, int lvl,
    int flags, dmar_pte_t *pte, struct sf_buf **sf, bool free_sf)
{
	vm_page_t m;

	dmar_pte_clear(&pte->pte);
	dmar_flush_pte_to_ram(domain->dmar, pte);
	m = sf_buf_page(*sf);
	if (free_sf) {
		dmar_unmap_pgtbl(*sf);
		*sf = NULL;
	}
	m->ref_count--;
	if (m->ref_count != 0)
		return;
	KASSERT(lvl != 0,
	    ("lost reference (lvl) on root pg domain %p base %jx lvl %d",
	    domain, (uintmax_t)base, lvl));
	KASSERT(m->pindex != 0,
	    ("lost reference (idx) on root pg domain %p base %jx lvl %d",
	    domain, (uintmax_t)base, lvl));
	dmar_pgfree(domain->pgtbl_obj, m->pindex, flags);
	domain_free_pgtbl_pde(domain, base, lvl - 1, flags);
}