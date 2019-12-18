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
typedef  scalar_t__ uint32_t ;
typedef  scalar_t__ uint16_t ;
struct vt_font_map {scalar_t__ vfm_src; scalar_t__ vfm_len; scalar_t__ vfm_dst; } ;

/* Variables and functions */

__attribute__((used)) static uint16_t
vtfont_bisearch(const struct vt_font_map *map, unsigned int len, uint32_t src)
{
	int min, mid, max;

	min = 0;
	max = len - 1;

	/* Empty font map. */
	if (len == 0)
		return (0);
	/* Character below minimal entry. */
	if (src < map[0].vfm_src)
		return (0);
	/* Optimization: ASCII characters occur very often. */
	if (src <= map[0].vfm_src + map[0].vfm_len)
		return (src - map[0].vfm_src + map[0].vfm_dst);
	/* Character above maximum entry. */
	if (src > map[max].vfm_src + map[max].vfm_len)
		return (0);

	/* Binary search. */
	while (max >= min) {
		mid = (min + max) / 2;
		if (src < map[mid].vfm_src)
			max = mid - 1;
		else if (src > map[mid].vfm_src + map[mid].vfm_len)
			min = mid + 1;
		else
			return (src - map[mid].vfm_src + map[mid].vfm_dst);
	}

	return (0);
}