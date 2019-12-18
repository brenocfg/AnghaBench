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
struct clknode_div_sc {int div_flags; struct clk_div_table* div_table; } ;
struct clk_div_table {scalar_t__ divider; scalar_t__ value; } ;

/* Variables and functions */
 int CLK_DIV_WITH_TABLE ; 
 int ENOENT ; 

__attribute__((used)) static int
clknode_div_table_get_value(struct clknode_div_sc *sc, uint32_t *divider)
{
	struct clk_div_table *table;

	if (!(sc->div_flags & CLK_DIV_WITH_TABLE))
		return (0);

	for (table = sc->div_table; table->divider != 0; table++)
		if (table->divider == *divider) {
			*divider = table->value;
			return (0);
		}

	return (ENOENT);
}