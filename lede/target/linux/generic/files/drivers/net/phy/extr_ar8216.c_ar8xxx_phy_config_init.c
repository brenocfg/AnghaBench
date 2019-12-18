#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ addr; } ;
struct phy_device {TYPE_2__ mdio; struct net_device* attached_dev; struct ar8xxx_priv* priv; } ;
struct net_device {int /*<<< orphan*/  eth_mangle_tx; int /*<<< orphan*/  eth_mangle_rx; int /*<<< orphan*/  priv_flags; struct ar8xxx_priv* phy_ptr; } ;
struct TYPE_6__ {scalar_t__ ports; } ;
struct ar8xxx_priv {int initialized; int port4_phy; TYPE_3__ dev; struct phy_device* phy; TYPE_1__* chip; } ;
struct TYPE_4__ {scalar_t__ config_at_probe; } ;

/* Variables and functions */
 scalar_t__ AR8216_NUM_PORTS ; 
 int ENODEV ; 
 int /*<<< orphan*/  IFF_NO_IP_ALIGN ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ar8216_mangle_rx ; 
 int /*<<< orphan*/  ar8216_mangle_tx ; 
 int /*<<< orphan*/  ar8316_hw_init (struct ar8xxx_priv*) ; 
 int ar8xxx_phy_check_aneg (struct phy_device*) ; 
 int ar8xxx_start (struct ar8xxx_priv*) ; 
 scalar_t__ chip_is_ar8216 (struct ar8xxx_priv*) ; 
 scalar_t__ chip_is_ar8316 (struct ar8xxx_priv*) ; 

__attribute__((used)) static int
ar8xxx_phy_config_init(struct phy_device *phydev)
{
	struct ar8xxx_priv *priv = phydev->priv;
	struct net_device *dev = phydev->attached_dev;
	int ret;

	if (WARN_ON(!priv))
		return -ENODEV;

	if (priv->chip->config_at_probe)
		return ar8xxx_phy_check_aneg(phydev);

	priv->phy = phydev;

	if (phydev->mdio.addr != 0) {
		if (chip_is_ar8316(priv)) {
			/* switch device has been initialized, reinit */
			priv->dev.ports = (AR8216_NUM_PORTS - 1);
			priv->initialized = false;
			priv->port4_phy = true;
			ar8316_hw_init(priv);
			return 0;
		}

		return 0;
	}

	ret = ar8xxx_start(priv);
	if (ret)
		return ret;

	/* VID fixup only needed on ar8216 */
	if (chip_is_ar8216(priv)) {
		dev->phy_ptr = priv;
		dev->priv_flags |= IFF_NO_IP_ALIGN;
		dev->eth_mangle_rx = ar8216_mangle_rx;
		dev->eth_mangle_tx = ar8216_mangle_tx;
	}

	return 0;
}