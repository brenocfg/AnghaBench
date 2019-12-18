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
typedef  int vm_offset_t ;
typedef  int pt_entry_t ;

/* Variables and functions */
 int PG_V ; 
 int /*<<< orphan*/  panic (char*) ; 
 int* vtopte (int) ; 

__attribute__((used)) static void
pmap_ptelist_free(vm_offset_t *head, vm_offset_t va)
{
	pt_entry_t *pte;

	if (va & PG_V)
		panic("pmap_ptelist_free: freeing va with PG_V set!");
	pte = vtopte(va);
	*pte = *head;		/* virtual! PG_V is 0 though */
	*head = va;
}