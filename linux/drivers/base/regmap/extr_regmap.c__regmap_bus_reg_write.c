#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct regmap {int /*<<< orphan*/  bus_context; TYPE_1__* bus; } ;
struct TYPE_2__ {int (* reg_write ) (int /*<<< orphan*/ ,unsigned int,unsigned int) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,unsigned int,unsigned int) ; 

__attribute__((used)) static int _regmap_bus_reg_write(void *context, unsigned int reg,
				 unsigned int val)
{
	struct regmap *map = context;

	return map->bus->reg_write(map->bus_context, reg, val);
}