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
typedef  int pdp_entry_t ;
typedef  int /*<<< orphan*/  pd_entry_t ;

/* Variables and functions */
 int* pmap_pdpe (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pdpe_to_pde (int*,int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline pd_entry_t *
pmap_pde(pmap_t pmap, vm_offset_t va)
{
	pdp_entry_t *pdpe;
	pt_entry_t PG_V;

	PG_V = pmap_valid_bit(pmap);
	pdpe = pmap_pdpe(pmap, va);
	if (pdpe == NULL || (*pdpe & PG_V) == 0)
		return (NULL);
	return (pmap_pdpe_to_pde(pdpe, va));
}