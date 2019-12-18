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
struct master {int /*<<< orphan*/  dev; struct component_match* match; } ;
struct component_match_array {int duplicate; struct component* component; } ;
struct component_match {size_t num; struct component_match_array* compare; } ;
struct component {struct master* master; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENXIO ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  dev_name (int /*<<< orphan*/ ) ; 
 struct component* find_component (struct master*,struct component_match_array*) ; 

__attribute__((used)) static int find_components(struct master *master)
{
	struct component_match *match = master->match;
	size_t i;
	int ret = 0;

	/*
	 * Scan the array of match functions and attach
	 * any components which are found to this master.
	 */
	for (i = 0; i < match->num; i++) {
		struct component_match_array *mc = &match->compare[i];
		struct component *c;

		dev_dbg(master->dev, "Looking for component %zu\n", i);

		if (match->compare[i].component)
			continue;

		c = find_component(master, mc);
		if (!c) {
			ret = -ENXIO;
			break;
		}

		dev_dbg(master->dev, "found component %s, duplicate %u\n", dev_name(c->dev), !!c->master);

		/* Attach this component to the master */
		match->compare[i].duplicate = !!c->master;
		match->compare[i].component = c;
		c->master = master;
	}
	return ret;
}