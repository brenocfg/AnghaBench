#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_4__ {int pm_type; } ;

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
 int* pat_index ; 
 int /*<<< orphan*/  pmap_is_valid_memattr (TYPE_1__*,int) ; 

int
pmap_cache_bits(pmap_t pmap, int mode, boolean_t is_pde)
{
	int cache_bits, pat_flag, pat_idx;

	if (!pmap_is_valid_memattr(pmap, mode))
		panic("Unknown caching mode %d\n", mode);

	switch (pmap->pm_type) {
	case PT_X86:
	case PT_RVI:
		/* The PAT bit is different for PTE's and PDE's. */
		pat_flag = is_pde ? X86_PG_PDE_PAT : X86_PG_PTE_PAT;

		/* Map the caching mode to a PAT index. */
		pat_idx = pat_index[mode];

		/* Map the 3-bit index value into the PAT, PCD, and PWT bits. */
		cache_bits = 0;
		if (pat_idx & 0x4)
			cache_bits |= pat_flag;
		if (pat_idx & 0x2)
			cache_bits |= PG_NC_PCD;
		if (pat_idx & 0x1)
			cache_bits |= PG_NC_PWT;
		break;

	case PT_EPT:
		cache_bits = EPT_PG_IGNORE_PAT | EPT_PG_MEMORY_TYPE(mode);
		break;

	default:
		panic("unsupported pmap type %d", pmap->pm_type);
	}

	return (cache_bits);
}