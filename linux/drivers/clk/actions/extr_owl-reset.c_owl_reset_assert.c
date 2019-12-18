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
struct reset_controller_dev {int dummy; } ;
struct owl_reset_map {int /*<<< orphan*/  bit; int /*<<< orphan*/  reg; } ;
struct owl_reset {int /*<<< orphan*/  regmap; struct owl_reset_map* reset_map; } ;

/* Variables and functions */
 int regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct owl_reset* to_owl_reset (struct reset_controller_dev*) ; 

__attribute__((used)) static int owl_reset_assert(struct reset_controller_dev *rcdev,
			    unsigned long id)
{
	struct owl_reset *reset = to_owl_reset(rcdev);
	const struct owl_reset_map *map = &reset->reset_map[id];

	return regmap_update_bits(reset->regmap, map->reg, map->bit, 0);
}