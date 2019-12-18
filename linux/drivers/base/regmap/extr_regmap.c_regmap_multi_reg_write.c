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
struct regmap {int /*<<< orphan*/  lock_arg; int /*<<< orphan*/  (* unlock ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* lock ) (int /*<<< orphan*/ ) ;} ;
struct reg_sequence {int dummy; } ;

/* Variables and functions */
 int _regmap_multi_reg_write (struct regmap*,struct reg_sequence const*,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int regmap_multi_reg_write(struct regmap *map, const struct reg_sequence *regs,
			   int num_regs)
{
	int ret;

	map->lock(map->lock_arg);

	ret = _regmap_multi_reg_write(map, regs, num_regs);

	map->unlock(map->lock_arg);

	return ret;
}