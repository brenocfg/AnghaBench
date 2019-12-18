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
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  M_VTD ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 scalar_t__ PHYS_TO_DMAP (int) ; 
 int VTD_PTE_ADDR_M ; 
 int VTD_PTE_RD ; 
 int VTD_PTE_SUPERPAGE ; 
 int VTD_PTE_WR ; 
 int /*<<< orphan*/  bzero (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vtd_free_ptp(uint64_t *ptp, int level)
{
	int i;
	uint64_t *nlp;

	if (level > 1) {
		for (i = 0; i < 512; i++) {
			if ((ptp[i] & (VTD_PTE_RD | VTD_PTE_WR)) == 0)
				continue;
			if ((ptp[i] & VTD_PTE_SUPERPAGE) != 0)
				continue;
			nlp = (uint64_t *)PHYS_TO_DMAP(ptp[i] & VTD_PTE_ADDR_M);
			vtd_free_ptp(nlp, level - 1);
		}
	}

	bzero(ptp, PAGE_SIZE);
	free(ptp, M_VTD);
}