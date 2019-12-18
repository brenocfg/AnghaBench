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
typedef  int aarch64_pte_t ;

/* Variables and functions */
 int AARCH64_ATTR_AP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AARCH64_ATTR_AP_RO ; 
 int AARCH64_ATTR_XN ; 
 int /*<<< orphan*/  VM_PROT_EXECUTE ; 
 int /*<<< orphan*/  VM_PROT_READ ; 
 int /*<<< orphan*/  VM_PROT_WRITE ; 

__attribute__((used)) static vm_prot_t
_aarch64_entry_to_prot(aarch64_pte_t pte)
{
	vm_prot_t prot = VM_PROT_READ;

	/* Source: arm64/arm64/pmap.c:pmap_protect() */
	if ((pte & AARCH64_ATTR_AP(AARCH64_ATTR_AP_RO)) == 0)
		prot |= VM_PROT_WRITE;
	if ((pte & AARCH64_ATTR_XN) == 0)
		prot |= VM_PROT_EXECUTE;
	return prot;
}