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
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  boolean_t ;
struct TYPE_3__ {int pm_type; } ;

/* Variables and functions */
 int EPT_PG_IGNORE_PAT ; 
 int EPT_PG_MEMORY_TYPE (int) ; 
#define  PT_EPT 130 
#define  PT_RVI 129 
#define  PT_X86 128 
 int X86_PG_PDE_CACHE ; 
 int X86_PG_PTE_CACHE ; 
 int /*<<< orphan*/  panic (char*,int) ; 

__attribute__((used)) static int
pmap_cache_mask(pmap_t pmap, boolean_t is_pde)
{
	int mask;

	switch (pmap->pm_type) {
	case PT_X86:
	case PT_RVI:
		mask = is_pde ? X86_PG_PDE_CACHE : X86_PG_PTE_CACHE;
		break;
	case PT_EPT:
		mask = EPT_PG_IGNORE_PAT | EPT_PG_MEMORY_TYPE(0x7);
		break;
	default:
		panic("pmap_cache_mask: invalid pm_type %d", pmap->pm_type);
	}

	return (mask);
}