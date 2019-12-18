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
typedef  int /*<<< orphan*/  u64 ;
struct nfit_set_info_map {int /*<<< orphan*/  region_offset; } ;

/* Variables and functions */
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int cmp_map_compat(const void *m0, const void *m1)
{
	const struct nfit_set_info_map *map0 = m0;
	const struct nfit_set_info_map *map1 = m1;

	return memcmp(&map0->region_offset, &map1->region_offset,
			sizeof(u64));
}