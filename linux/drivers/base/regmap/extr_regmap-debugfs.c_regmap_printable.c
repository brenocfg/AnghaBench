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
struct regmap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  regmap_cached (struct regmap*,unsigned int) ; 
 scalar_t__ regmap_precious (struct regmap*,unsigned int) ; 
 int /*<<< orphan*/  regmap_readable (struct regmap*,unsigned int) ; 

__attribute__((used)) static bool regmap_printable(struct regmap *map, unsigned int reg)
{
	if (regmap_precious(map, reg))
		return false;

	if (!regmap_readable(map, reg) && !regmap_cached(map, reg))
		return false;

	return true;
}