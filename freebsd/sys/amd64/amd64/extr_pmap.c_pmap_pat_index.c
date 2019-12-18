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
 int EPT_PG_IGNORE_PAT ; 
 int EPT_PG_MEMORY_TYPE (int) ; 
 int PG_NC_PCD ; 
 int PG_NC_PWT ; 
#define  PT_EPT 130 
#define  PT_RVI 129 
#define  PT_X86 128 
 int X86_PG_PDE_PAT ; 
 int X86_PG_PTE_PAT ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
pmap_pat_index(pmap_t pmap, pt_entry_t pte, bool is_pde)
{
	int pat_flag, pat_idx;

	pat_idx = 0;
	switch (pmap->pm_type) {
	case PT_X86:
	case PT_RVI:
		/* The PAT bit is different for PTE's and PDE's. */
		pat_flag = is_pde ? X86_PG_PDE_PAT : X86_PG_PTE_PAT;

		if ((pte & pat_flag) != 0)
			pat_idx |= 0x4;
		if ((pte & PG_NC_PCD) != 0)
			pat_idx |= 0x2;
		if ((pte & PG_NC_PWT) != 0)
			pat_idx |= 0x1;
		break;
	case PT_EPT:
		if ((pte & EPT_PG_IGNORE_PAT) != 0)
			panic("EPT PTE %#lx has no PAT memory type", pte);
		pat_idx = (pte & EPT_PG_MEMORY_TYPE(0x7)) >> 3;
		break;
	}

	/* See pmap_init_pat(). */
	if (pat_idx == 4)
		pat_idx = 0;
	if (pat_idx == 7)
		pat_idx = 3;

	return (pat_idx);
}