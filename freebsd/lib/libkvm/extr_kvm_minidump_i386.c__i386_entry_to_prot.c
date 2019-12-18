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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int I386_PG_NX ; 
 int I386_PG_RW ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 

__attribute__((used)) static vm_prot_t
_i386_entry_to_prot(uint64_t pte)
{
	vm_prot_t prot = VM_PROT_READ;

	/* Source: i386/pmap.c:pmap_protect() */
	if (pte & I386_PG_RW)
		prot |= VM_PROT_WRITE;
	if ((pte & I386_PG_NX) == 0)
		prot |= VM_PROT_EXECUTE;

	return prot;
}