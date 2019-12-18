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
struct regmap_range_node {unsigned int range_min; unsigned int window_len; } ;
struct regmap {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int _regmap_register_page(struct regmap *map,
					  unsigned int reg,
					  struct regmap_range_node *range)
{
	unsigned int win_page = (reg - range->range_min) / range->window_len;

	return win_page;
}