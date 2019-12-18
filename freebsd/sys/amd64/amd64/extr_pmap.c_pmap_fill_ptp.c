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
typedef  int /*<<< orphan*/  pt_entry_t ;

/* Variables and functions */
 int NPTEPG ; 
 scalar_t__ PAGE_SIZE ; 

__attribute__((used)) static void
pmap_fill_ptp(pt_entry_t *firstpte, pt_entry_t newpte)
{
	pt_entry_t *pte;

	for (pte = firstpte; pte < firstpte + NPTEPG; pte++) {
		*pte = newpte;
		newpte += PAGE_SIZE;
	}
}