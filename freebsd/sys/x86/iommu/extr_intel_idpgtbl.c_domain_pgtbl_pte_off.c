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
struct dmar_domain {int pglvl; } ;
typedef  int dmar_gaddr_t ;

/* Variables and functions */
 int DMAR_NPTEPGSHIFT ; 
 int DMAR_PAGE_SHIFT ; 
 int DMAR_PTEMASK ; 

__attribute__((used)) static int
domain_pgtbl_pte_off(struct dmar_domain *domain, dmar_gaddr_t base, int lvl)
{

	base >>= DMAR_PAGE_SHIFT + (domain->pglvl - lvl - 1) *
	    DMAR_NPTEPGSHIFT;
	return (base & DMAR_PTEMASK);
}