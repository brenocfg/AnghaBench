#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ format_reg; scalar_t__ format_val; } ;
struct regmap {TYPE_2__ format; TYPE_1__* bus; } ;
struct TYPE_3__ {scalar_t__ write; } ;

/* Variables and functions */

bool regmap_can_raw_write(struct regmap *map)
{
	return map->bus && map->bus->write && map->format.format_val &&
		map->format.format_reg;
}