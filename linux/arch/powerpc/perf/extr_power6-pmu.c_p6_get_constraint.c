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
typedef  int u64 ;

/* Variables and functions */
 int PM_BUSEVENT_MSK ; 
 int PM_BYTE_MSK ; 
 int PM_BYTE_SH ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_SUBUNIT_MSK ; 
 int PM_SUBUNIT_SH ; 
 int PM_UNIT_MSKS ; 
 int PM_UNIT_SH ; 

__attribute__((used)) static int p6_get_constraint(u64 event, unsigned long *maskp,
			     unsigned long *valp)
{
	int pmc, byte, sh, subunit;
	unsigned long mask = 0, value = 0;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 4 && !(event == 0x500009 || event == 0x600005))
			return -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
	}
	if (event & PM_BUSEVENT_MSK) {
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		sh = byte * 4 + (16 - PM_UNIT_SH);
		mask |= PM_UNIT_MSKS << sh;
		value |= (unsigned long)(event & PM_UNIT_MSKS) << sh;
		if ((event & PM_UNIT_MSKS) == (5 << PM_UNIT_SH)) {
			subunit = (event >> PM_SUBUNIT_SH) & PM_SUBUNIT_MSK;
			mask  |= (unsigned long)PM_SUBUNIT_MSK << 32;
			value |= (unsigned long)subunit << 32;
		}
	}
	if (pmc <= 4) {
		mask  |= 0x8000;	/* add field for count of PMC1-4 uses */
		value |= 0x1000;
	}
	*maskp = mask;
	*valp = value;
	return 0;
}