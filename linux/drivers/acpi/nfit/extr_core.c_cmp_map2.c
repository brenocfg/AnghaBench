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
struct nfit_set_info_map2 {scalar_t__ region_offset; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_map2(const void *m0, const void *m1)
{
	const struct nfit_set_info_map2 *map0 = m0;
	const struct nfit_set_info_map2 *map1 = m1;

	if (map0->region_offset < map1->region_offset)
		return -1;
	else if (map0->region_offset > map1->region_offset)
		return 1;
	return 0;
}