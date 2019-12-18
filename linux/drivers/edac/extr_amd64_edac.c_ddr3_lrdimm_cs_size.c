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

/* Variables and functions */

__attribute__((used)) static int ddr3_lrdimm_cs_size(unsigned i, unsigned rank_multiply)
{
	unsigned shift = 0;
	int cs_size = 0;

	if (i < 4 || i == 6)
		cs_size = -1;
	else if (i == 12)
		shift = 7;
	else if (!(i & 0x1))
		shift = i >> 1;
	else
		shift = (i + 1) >> 1;

	if (cs_size != -1)
		cs_size = rank_multiply * (128 << shift);

	return cs_size;
}