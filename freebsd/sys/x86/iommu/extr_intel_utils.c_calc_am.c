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
struct dmar_unit {int /*<<< orphan*/  hw_cap; } ;
typedef  int dmar_gaddr_t ;

/* Variables and functions */
 int DMAR_CAP_MAMV (int /*<<< orphan*/ ) ; 
 int DMAR_PAGE_SHIFT ; 

int
calc_am(struct dmar_unit *unit, dmar_gaddr_t base, dmar_gaddr_t size,
    dmar_gaddr_t *isizep)
{
	dmar_gaddr_t isize;
	int am;

	for (am = DMAR_CAP_MAMV(unit->hw_cap);; am--) {
		isize = 1ULL << (am + DMAR_PAGE_SHIFT);
		if ((base & (isize - 1)) == 0 && size >= isize)
			break;
		if (am == 0)
			break;
	}
	*isizep = isize;
	return (am);
}