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
struct cpuinfo_mips {unsigned int tlbsize; unsigned int tlbsizevtlb; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int calculate_ftlb_probability(struct cpuinfo_mips *c)
{

	unsigned int probability = c->tlbsize / c->tlbsizevtlb;

	/*
	 * 0 = All TLBWR instructions go to FTLB
	 * 1 = 15:1: For every 16 TBLWR instructions, 15 go to the
	 * FTLB and 1 goes to the VTLB.
	 * 2 = 7:1: As above with 7:1 ratio.
	 * 3 = 3:1: As above with 3:1 ratio.
	 *
	 * Use the linear midpoint as the probability threshold.
	 */
	if (probability >= 12)
		return 1;
	else if (probability >= 6)
		return 2;
	else
		/*
		 * So FTLB is less than 4 times bigger than VTLB.
		 * A 3:1 ratio can still be useful though.
		 */
		return 3;
}