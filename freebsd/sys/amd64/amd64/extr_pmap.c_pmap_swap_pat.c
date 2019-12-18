#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int pt_entry_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_3__ {int pm_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
#define  PT_EPT 130 
#define  PT_RVI 129 
#define  PT_X86 128 
 int X86_PG_PDE_PAT ; 
 int X86_PG_PTE_PAT ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static pt_entry_t
pmap_swap_pat(pmap_t pmap, pt_entry_t entry)
{
	int x86_pat_bits = X86_PG_PTE_PAT | X86_PG_PDE_PAT;

	switch (pmap->pm_type) {
	case PT_X86:
	case PT_RVI:
		/* Verify that both PAT bits are not set at the same time */
		KASSERT((entry & x86_pat_bits) != x86_pat_bits,
		    ("Invalid PAT bits in entry %#lx", entry));

		/* Swap the PAT bits if one of them is set */
		if ((entry & x86_pat_bits) != 0)
			entry ^= x86_pat_bits;
		break;
	case PT_EPT:
		/*
		 * Nothing to do - the memory attributes are represented
		 * the same way for regular pages and superpages.
		 */
		break;
	default:
		panic("pmap_switch_pat_bits: bad pm_type %d", pmap->pm_type);
	}

	return (entry);
}