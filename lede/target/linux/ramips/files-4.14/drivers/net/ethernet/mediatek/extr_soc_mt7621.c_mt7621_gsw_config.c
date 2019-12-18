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
struct fe_priv {scalar_t__ mii_bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ mdiobus_get_phy (scalar_t__,int) ; 
 int /*<<< orphan*/  mt7530_probe (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int) ; 

__attribute__((used)) static int mt7621_gsw_config(struct fe_priv *priv)
{
	if (priv->mii_bus &&  mdiobus_get_phy(priv->mii_bus, 0x1f))
		mt7530_probe(priv->dev, NULL, priv->mii_bus, 1);

	return 0;
}