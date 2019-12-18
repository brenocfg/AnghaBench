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
 int PM_GRS ; 
 int PM_GRS_SH ; 
 int PM_ISU0 ; 
 int PM_ISU0_ALT ; 
 int PM_LASTUNIT ; 
 int PM_LSU1 ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_UNIT_MSK ; 
 int PM_UNIT_SH ; 
 int* grsel_shift ; 
 unsigned long** unit_cons ; 

__attribute__((used)) static int power5_get_constraint(u64 event, unsigned long *maskp,
				 unsigned long *valp)
{
	int pmc, byte, unit, sh;
	int bit, fmask;
	unsigned long mask = 0, value = 0;
	int grp = -1;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	if (pmc) {
		if (pmc > 6)
			return -1;
		sh = (pmc - 1) * 2;
		mask |= 2 << sh;
		value |= 1 << sh;
		if (pmc <= 4)
			grp = (pmc - 1) >> 1;
		else if (event != 0x500009 && event != 0x600005)
			return -1;
	}
	if (event & PM_BUSEVENT_MSK) {
		unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
		if (unit > PM_LASTUNIT)
			return -1;
		if (unit == PM_ISU0_ALT)
			unit = PM_ISU0;
		mask |= unit_cons[unit][0];
		value |= unit_cons[unit][1];
		byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
		if (byte >= 4) {
			if (unit != PM_LSU1)
				return -1;
			/* Map LSU1 low word (bytes 4-7) to unit LSU1+1 */
			++unit;
			byte &= 3;
		}
		if (unit == PM_GRS) {
			bit = event & 7;
			fmask = (bit == 6)? 7: 3;
			sh = grsel_shift[bit];
			mask |= (unsigned long)fmask << sh;
			value |= (unsigned long)((event >> PM_GRS_SH) & fmask)
				<< sh;
		}
		/*
		 * Bus events on bytes 0 and 2 can be counted
		 * on PMC1/2; bytes 1 and 3 on PMC3/4.
		 */
		if (!pmc)
			grp = byte & 1;
		/* Set byte lane select field */
		mask  |= 0xfUL << (24 - 4 * byte);
		value |= (unsigned long)unit << (24 - 4 * byte);
	}
	if (grp == 0) {
		/* increment PMC1/2 field */
		mask  |= 0x200000000ul;
		value |= 0x080000000ul;
	} else if (grp == 1) {
		/* increment PMC3/4 field */
		mask  |= 0x40000000ul;
		value |= 0x10000000ul;
	}
	if (pmc < 5) {
		/* need a counter from PMC1-4 set */
		mask  |= 0x8000000000000ul;
		value |= 0x1000000000000ul;
	}
	*maskp = mask;
	*valp = value;
	return 0;
}