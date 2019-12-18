#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct resource {int start; } ;
struct TYPE_2__ {int /*<<< orphan*/  of_node; } ;
struct platform_device {TYPE_1__ dev; } ;
struct mii_bus {char* name; int /*<<< orphan*/  id; TYPE_1__* parent; } ;
struct device_node {int dummy; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 struct mii_bus* alloc_mdio_bitbang (int /*<<< orphan*/ *) ; 
 struct device_node* ep8248e_bcsr_node ; 
 int /*<<< orphan*/  ep8248e_mdio_ctrl ; 
 int /*<<< orphan*/  free_mdio_bitbang (struct mii_bus*) ; 
 int of_address_to_resource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct resource*) ; 
 struct device_node* of_get_parent (int /*<<< orphan*/ ) ; 
 int of_mdiobus_register (struct mii_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int ep8248e_mdio_probe(struct platform_device *ofdev)
{
	struct mii_bus *bus;
	struct resource res;
	struct device_node *node;
	int ret;

	node = of_get_parent(ofdev->dev.of_node);
	of_node_put(node);
	if (node != ep8248e_bcsr_node)
		return -ENODEV;

	ret = of_address_to_resource(ofdev->dev.of_node, 0, &res);
	if (ret)
		return ret;

	bus = alloc_mdio_bitbang(&ep8248e_mdio_ctrl);
	if (!bus)
		return -ENOMEM;

	bus->name = "ep8248e-mdio-bitbang";
	bus->parent = &ofdev->dev;
	snprintf(bus->id, MII_BUS_ID_SIZE, "%x", res.start);

	ret = of_mdiobus_register(bus, ofdev->dev.of_node);
	if (ret)
		goto err_free_bus;

	return 0;
err_free_bus:
	free_mdio_bitbang(bus);
	return ret;
}