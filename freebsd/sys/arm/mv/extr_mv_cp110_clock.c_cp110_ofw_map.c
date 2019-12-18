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
typedef  int uint32_t ;
struct clknode {int dummy; } ;
struct clkdom {int dummy; } ;
typedef  int phandle_t ;

/* Variables and functions */
 scalar_t__ CP110_MAX_CLOCK ; 
 int ENXIO ; 
 struct clknode* clknode_find_by_id (struct clkdom*,int) ; 

__attribute__((used)) static int
cp110_ofw_map(struct clkdom *clkdom, uint32_t ncells,
    phandle_t *cells, struct clknode **clk)
{
	int id = 0;

	if (ncells != 2)
		return (ENXIO);

	id = cells[1];
	if (cells[0] == 1)
		id += CP110_MAX_CLOCK;

	*clk = clknode_find_by_id(clkdom, id);

	return (0);
}