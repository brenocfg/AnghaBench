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
struct tegra124_init_item {scalar_t__ frequency; scalar_t__ enable; int /*<<< orphan*/  name; int /*<<< orphan*/ * parent; } ;
struct tegra124_car_softc {int /*<<< orphan*/  dev; } ;
struct clknode {int dummy; } ;

/* Variables and functions */
 struct tegra124_init_item* clk_init_table ; 
 int clknode_enable (struct clknode*) ; 
 struct clknode* clknode_find_by_name (int /*<<< orphan*/ ) ; 
 int clknode_set_freq (struct clknode*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 int clknode_set_parent_by_name (struct clknode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int nitems (struct tegra124_init_item*) ; 

__attribute__((used)) static void
postinit_clock(struct tegra124_car_softc *sc)
{
	int i;
	struct tegra124_init_item *tbl;
	struct clknode *clknode;
	int rv;

	for (i = 0; i < nitems(clk_init_table); i++) {
		tbl = &clk_init_table[i];

		clknode =  clknode_find_by_name(tbl->name);
		if (clknode == NULL) {
			device_printf(sc->dev, "Cannot find clock %s\n",
			    tbl->name);
			continue;
		}
		if (tbl->parent != NULL) {
			rv = clknode_set_parent_by_name(clknode, tbl->parent);
			if (rv != 0) {
				device_printf(sc->dev,
				    "Cannot set parent for %s (to %s): %d\n",
				    tbl->name, tbl->parent, rv);
				continue;
			}
		}
		if (tbl->frequency != 0) {
			rv = clknode_set_freq(clknode, tbl->frequency, 0 , 9999);
			if (rv != 0) {
				device_printf(sc->dev,
				    "Cannot set frequency for %s: %d\n",
				    tbl->name, rv);
				continue;
			}
		}
		if (tbl->enable!= 0) {
			rv = clknode_enable(clknode);
			if (rv != 0) {
				device_printf(sc->dev,
				    "Cannot enable %s: %d\n", tbl->name, rv);
				continue;
			}
		}
	}
}