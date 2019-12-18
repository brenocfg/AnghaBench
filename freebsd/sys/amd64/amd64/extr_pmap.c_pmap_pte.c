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
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int pd_entry_t ;

/* Variables and functions */
 int PG_PS ; 
 int* pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* pmap_pde_to_pte (int*,int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline pt_entry_t *
pmap_pte(pmap_t pmap, vm_offset_t va)
{
	pd_entry_t *pde;
	pt_entry_t PG_V;

	PG_V = pmap_valid_bit(pmap);
	pde = pmap_pde(pmap, va);
	if (pde == NULL || (*pde & PG_V) == 0)
		return (NULL);
	if ((*pde & PG_PS) != 0)	/* compat with i386 pmap_pte() */
		return ((pt_entry_t *)pde);
	return (pmap_pde_to_pte(pde, va));
}