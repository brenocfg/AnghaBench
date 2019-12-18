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
struct platform_device {int /*<<< orphan*/  dev; } ;
struct mii_bus {int /*<<< orphan*/ * priv; } ;

/* Variables and functions */
 struct mii_bus* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mdiobus_free (struct mii_bus*) ; 
 int /*<<< orphan*/  mdiobus_unregister (struct mii_bus*) ; 

__attribute__((used)) static int gpio_mdio_remove(struct platform_device *dev)
{
	struct mii_bus *bus = dev_get_drvdata(&dev->dev);

	mdiobus_unregister(bus);

	dev_set_drvdata(&dev->dev, NULL);

	kfree(bus->priv);
	bus->priv = NULL;
	mdiobus_free(bus);

	return 0;
}