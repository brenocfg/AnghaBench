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
 int PM_BYTE_MSK ; 
 int PM_BYTE_SH ; 
#define  PM_LSU0 130 
#define  PM_LSU1L 129 
 int PM_PMCSEL_MSK ; 
 int PM_PMC_MSK ; 
 int PM_PMC_SH ; 
 int PM_UNIT_MSK ; 
 int PM_UNIT_SH ; 
#define  PM_VPU 128 
 int* direct_marked_event ; 

__attribute__((used)) static int p970_marked_instr_event(u64 event)
{
	int pmc, psel, unit, byte, bit;
	unsigned int mask;

	pmc = (event >> PM_PMC_SH) & PM_PMC_MSK;
	psel = event & PM_PMCSEL_MSK;
	if (pmc) {
		if (direct_marked_event[pmc - 1] & (1 << psel))
			return 1;
		if (psel == 0)		/* add events */
			bit = (pmc <= 4)? pmc - 1: 8 - pmc;
		else if (psel == 7 || psel == 13)	/* decode events */
			bit = 4;
		else
			return 0;
	} else
		bit = psel;

	byte = (event >> PM_BYTE_SH) & PM_BYTE_MSK;
	unit = (event >> PM_UNIT_SH) & PM_UNIT_MSK;
	mask = 0;
	switch (unit) {
	case PM_VPU:
		mask = 0x4c;		/* byte 0 bits 2,3,6 */
		break;
	case PM_LSU0:
		/* byte 2 bits 0,2,3,4,6; all of byte 1 */
		mask = 0x085dff00;
		break;
	case PM_LSU1L:
		mask = 0x50 << 24;	/* byte 3 bits 4,6 */
		break;
	}
	return (mask >> (byte * 8 + bit)) & 1;
}