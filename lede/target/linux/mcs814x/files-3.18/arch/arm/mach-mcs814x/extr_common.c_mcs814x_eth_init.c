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
 int /*<<< orphan*/  be32_to_cpup (unsigned int const*) ; 
 int /*<<< orphan*/  mcs814x_eth_buffer_shifting_set (int) ; 
 int /*<<< orphan*/  mcs814x_eth_hardware_filter_set (int) ; 
 int /*<<< orphan*/  mcs814x_eth_ids ; 
 int /*<<< orphan*/  mcs814x_eth_led_cfg_set (int /*<<< orphan*/ ) ; 
 struct device_node* of_find_matching_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 unsigned int* of_get_property (struct device_node*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 

__attribute__((used)) static void mcs814x_eth_init(void)
{
	struct device_node *np;
	const unsigned int *intspec;

	np = of_find_matching_node(NULL, mcs814x_eth_ids);
	if (!np)
		return;

	/* hardware filter must always be enabled */
	mcs814x_eth_hardware_filter_set(1);

	intspec = of_get_property(np, "nuport-mac,buffer-shifting", NULL);
	if (!intspec)
		mcs814x_eth_buffer_shifting_set(0);
	else
		mcs814x_eth_buffer_shifting_set(1);

	intspec = of_get_property(np, "nuport-mac,link-activity", NULL);
	if (intspec)
		mcs814x_eth_led_cfg_set(be32_to_cpup(intspec));

	of_node_put(np);
}