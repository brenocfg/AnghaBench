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
struct switch_dev {int vlans; } ;
struct ar8xxx_priv {int* pvid; } ;

/* Variables and functions */
 int AR8X16_MAX_PORTS ; 
 int EINVAL ; 
 struct ar8xxx_priv* swdev_to_ar8xxx (struct switch_dev*) ; 

int
ar8xxx_sw_set_pvid(struct switch_dev *dev, int port, int vlan)
{
	struct ar8xxx_priv *priv = swdev_to_ar8xxx(dev);

	/* make sure no invalid PVIDs get set */

	if (vlan < 0 || vlan >= dev->vlans ||
	    port < 0 || port >= AR8X16_MAX_PORTS)
		return -EINVAL;

	priv->pvid[port] = vlan;
	return 0;
}