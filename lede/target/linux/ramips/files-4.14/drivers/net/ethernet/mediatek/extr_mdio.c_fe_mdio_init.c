#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct fe_priv {TYPE_3__* mii_bus; TYPE_6__* dev; TYPE_1__* soc; TYPE_2__* phy; } ;
struct device_node {char* name; } ;
struct TYPE_10__ {int /*<<< orphan*/  of_node; } ;
struct TYPE_9__ {char* name; int /*<<< orphan*/  id; TYPE_6__* parent; struct fe_priv* priv; int /*<<< orphan*/  reset; scalar_t__ write; scalar_t__ read; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {scalar_t__ mdio_write; scalar_t__ mdio_read; } ;

/* Variables and functions */
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  MII_BUS_ID_SIZE ; 
 int /*<<< orphan*/  dev_err (TYPE_6__*,char*,char*) ; 
 int /*<<< orphan*/  fe_mdio_reset ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* mdiobus_alloc () ; 
 int /*<<< orphan*/  of_device_is_available (struct device_node*) ; 
 struct device_node* of_get_child_by_name (int /*<<< orphan*/ ,char*) ; 
 int of_mdiobus_register (TYPE_3__*,struct device_node*) ; 
 int /*<<< orphan*/  of_node_put (struct device_node*) ; 
 TYPE_2__ phy_ralink ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int fe_mdio_init(struct fe_priv *priv)
{
	struct device_node *mii_np;
	int err;

	if (!priv->soc->mdio_read || !priv->soc->mdio_write)
		return 0;

	spin_lock_init(&phy_ralink.lock);
	priv->phy = &phy_ralink;

	mii_np = of_get_child_by_name(priv->dev->of_node, "mdio-bus");
	if (!mii_np) {
		dev_err(priv->dev, "no %s child node found", "mdio-bus");
		return -ENODEV;
	}

	if (!of_device_is_available(mii_np)) {
		err = 0;
		goto err_put_node;
	}

	priv->mii_bus = mdiobus_alloc();
	if (!priv->mii_bus) {
		err = -ENOMEM;
		goto err_put_node;
	}

	priv->mii_bus->name = "mdio";
	priv->mii_bus->read = priv->soc->mdio_read;
	priv->mii_bus->write = priv->soc->mdio_write;
	priv->mii_bus->reset = fe_mdio_reset;
	priv->mii_bus->priv = priv;
	priv->mii_bus->parent = priv->dev;

	snprintf(priv->mii_bus->id, MII_BUS_ID_SIZE, "%s", mii_np->name);
	err = of_mdiobus_register(priv->mii_bus, mii_np);
	if (err)
		goto err_free_bus;

	return 0;

err_free_bus:
	kfree(priv->mii_bus);
err_put_node:
	of_node_put(mii_np);
	priv->mii_bus = NULL;
	return err;
}