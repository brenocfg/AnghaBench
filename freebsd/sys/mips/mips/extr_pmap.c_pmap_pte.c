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
typedef  int /*<<< orphan*/  pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/ * pd_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ ** pmap_pde (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pde_to_pte (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

pt_entry_t *
pmap_pte(pmap_t pmap, vm_offset_t va)
{
	pd_entry_t *pde;

	pde = pmap_pde(pmap, va);
	if (pde == NULL || *pde == NULL)
		return (NULL);

	return (pmap_pde_to_pte(pde, va));
}