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
struct net_device {int dummy; } ;
struct fe_priv {struct net_device* netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_close (struct net_device*) ; 
 int fe_open (struct net_device*) ; 
 int /*<<< orphan*/  fe_stop (struct net_device*) ; 
 int /*<<< orphan*/  ifup ; 
 int /*<<< orphan*/  netif_alert (struct fe_priv*,int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void fe_reset_pending(struct fe_priv *priv)
{
	struct net_device *dev = priv->netdev;
	int err;

	rtnl_lock();
	fe_stop(dev);

	err = fe_open(dev);
	if (err) {
		netif_alert(priv, ifup, dev,
			    "Driver up/down cycle failed, closing device.\n");
		dev_close(dev);
	}
	rtnl_unlock();
}