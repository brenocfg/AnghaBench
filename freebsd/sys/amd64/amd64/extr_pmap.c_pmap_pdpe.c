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
typedef  int pml4_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;
typedef  int /*<<< orphan*/  pdp_entry_t ;

/* Variables and functions */
 int* pmap_pml4e (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pmap_pml4e_to_pdpe (int*,int /*<<< orphan*/ ) ; 
 int pmap_valid_bit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline pdp_entry_t *
pmap_pdpe(pmap_t pmap, vm_offset_t va)
{
	pml4_entry_t *pml4e;
	pt_entry_t PG_V;

	PG_V = pmap_valid_bit(pmap);
	pml4e = pmap_pml4e(pmap, va);
	if ((*pml4e & PG_V) == 0)
		return (NULL);
	return (pmap_pml4e_to_pdpe(pml4e, va));
}