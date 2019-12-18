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
typedef  int u_int ;
typedef  int off_t ;

/* Variables and functions */

void
g_part_geometry_heads(off_t blocks, u_int sectors, off_t *bestchs,
    u_int *bestheads)
{
	static u_int candidate_heads[] = { 1, 2, 16, 32, 64, 128, 255, 0 };
	off_t chs, cylinders;
	u_int heads;
	int idx;

	*bestchs = 0;
	*bestheads = 0;
	for (idx = 0; candidate_heads[idx] != 0; idx++) {
		heads = candidate_heads[idx];
		cylinders = blocks / heads / sectors;
		if (cylinders < heads || cylinders < sectors)
			break;
		if (cylinders > 1023)
			continue;
		chs = cylinders * heads * sectors;
		if (chs > *bestchs || (chs == *bestchs && *bestheads == 1)) {
			*bestchs = chs;
			*bestheads = heads;
		}
	}
}