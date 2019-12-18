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
struct device_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  of_find_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 char* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static int of_bus_simba_match(struct device_node *np)
{
	const char *model = of_get_property(np, "model", NULL);

	if (model && !strcmp(model, "SUNW,simba"))
		return 1;

	/* Treat PCI busses lacking ranges property just like
	 * simba.
	 */
	if (of_node_name_eq(np, "pci")) {
		if (!of_find_property(np, "ranges", NULL))
			return 1;
	}

	return 0;
}