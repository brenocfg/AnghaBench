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
 int ENODEV ; 
 int /*<<< orphan*/  gpio_mdio_driver ; 
 int /*<<< orphan*/  gpio_regs ; 
 struct device_node* of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  of_iomap (struct device_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int platform_driver_register (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gpio_mdio_init(void)
{
	struct device_node *np;

	np = of_find_compatible_node(NULL, NULL, "1682m-gpio");
	if (!np)
		np = of_find_compatible_node(NULL, NULL,
					     "pasemi,pwrficient-gpio");
	if (!np)
		return -ENODEV;
	gpio_regs = of_iomap(np, 0);
	of_node_put(np);

	if (!gpio_regs)
		return -ENODEV;

	return platform_driver_register(&gpio_mdio_driver);
}