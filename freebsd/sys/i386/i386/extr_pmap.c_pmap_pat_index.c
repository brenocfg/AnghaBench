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
typedef  int pt_entry_t ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int CPUID_PAT ; 
 int PG_NC_PCD ; 
 int PG_NC_PWT ; 
 int PG_PDE_PAT ; 
 int PG_PTE_PAT ; 
 int cpu_feature ; 
 scalar_t__ pat_works ; 

__attribute__((used)) static int
pmap_pat_index(pmap_t pmap, pt_entry_t pte, bool is_pde)
{
	int pat_flag, pat_idx;

	if ((cpu_feature & CPUID_PAT) == 0)
		return (0);

	pat_idx = 0;
	/* The PAT bit is different for PTE's and PDE's. */
	pat_flag = is_pde ? PG_PDE_PAT : PG_PTE_PAT;

	if ((pte & pat_flag) != 0)
		pat_idx |= 0x4;
	if ((pte & PG_NC_PCD) != 0)
		pat_idx |= 0x2;
	if ((pte & PG_NC_PWT) != 0)
		pat_idx |= 0x1;

	/* See pmap_init_pat(). */
	if (pat_works) {
		if (pat_idx == 4)
			pat_idx = 0;
		if (pat_idx == 7)
			pat_idx = 3;
	} else {
		/* XXXKIB */
	}

	return (pat_idx);
}