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
typedef  int uint8_t ;
typedef  int rman_res_t ;

/* Variables and functions */

__attribute__((used)) static int
apb_checkrange(uint8_t map, rman_res_t scale, rman_res_t start, rman_res_t end)
{
	int i, ei;

	i = start / scale;
	ei = end / scale;
	if (i > 7 || ei > 7)
		return (0);
	for (; i <= ei; i++)
		if ((map & (1 << i)) == 0)
			return (0);
	return (1);
}