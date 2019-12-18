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
struct device_node {struct device_node* parent; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_device_is_compatible (struct device_node*,char*) ; 
 scalar_t__ of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int omap_timer_add_disabled_property (struct device_node*) ; 

__attribute__((used)) static int omap_timer_update_dt(struct device_node *np)
{
	int error = 0;

	if (!of_device_is_compatible(np, "ti,omap-counter32k")) {
		error = omap_timer_add_disabled_property(np);
		if (error)
			return error;
	}

	/* No parent interconnect target module configured? */
	if (of_get_property(np, "ti,hwmods", NULL))
		return error;

	/* Tag parent interconnect target module disabled */
	error = omap_timer_add_disabled_property(np->parent);
	if (error)
		return error;

	return 0;
}