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
 int /*<<< orphan*/  DBG (char*,struct device_node*) ; 
 int /*<<< orphan*/  PMF_FLAGS_ON_INIT ; 
 struct device_node* of_get_next_child (struct device_node*,struct device_node*) ; 
 scalar_t__ of_node_name_eq (struct device_node*,char*) ; 
 int /*<<< orphan*/  pmf_do_functions (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmf_register_driver (struct device_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct device_node* unin_hwclock ; 
 int /*<<< orphan*/  unin_mmio_handlers ; 
 struct device_node* uninorth_node ; 

__attribute__((used)) static void uninorth_install_pfunc(void)
{
	struct device_node *np;

	DBG("Installing functions for UniN %pOF\n",
	    uninorth_node);

	/*
	 * Install handlers for the bridge itself
	 */
	pmf_register_driver(uninorth_node, &unin_mmio_handlers, NULL);
	pmf_do_functions(uninorth_node, NULL, 0, PMF_FLAGS_ON_INIT, NULL);


	/*
	 * Install handlers for the hwclock child if any
	 */
	for (np = NULL; (np = of_get_next_child(uninorth_node, np)) != NULL;)
		if (of_node_name_eq(np, "hw-clock")) {
			unin_hwclock = np;
			break;
		}
	if (unin_hwclock) {
		DBG("Installing functions for UniN clock %pOF\n",
		    unin_hwclock);
		pmf_register_driver(unin_hwclock, &unin_mmio_handlers, NULL);
		pmf_do_functions(unin_hwclock, NULL, 0, PMF_FLAGS_ON_INIT,
				 NULL);
	}
}