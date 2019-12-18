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
struct omap_hwmod {int /*<<< orphan*/  name; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int of_property_count_strings (struct device_node*,char*) ; 
 int of_property_read_string_index (struct device_node*,char*,int,char const**) ; 
 int /*<<< orphan*/  pr_debug (char*,struct device_node*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int of_dev_find_hwmod(struct device_node *np,
			     struct omap_hwmod *oh)
{
	int count, i, res;
	const char *p;

	count = of_property_count_strings(np, "ti,hwmods");
	if (count < 1)
		return -ENODEV;

	for (i = 0; i < count; i++) {
		res = of_property_read_string_index(np, "ti,hwmods",
						    i, &p);
		if (res)
			continue;
		if (!strcmp(p, oh->name)) {
			pr_debug("omap_hwmod: dt %pOFn[%i] uses hwmod %s\n",
				 np, i, oh->name);
			return i;
		}
	}

	return -ENODEV;
}