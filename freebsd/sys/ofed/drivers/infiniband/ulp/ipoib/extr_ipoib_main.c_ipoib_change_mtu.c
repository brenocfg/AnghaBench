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
struct ipoib_dev_priv {int mcast_mtu; int admin_mtu; int /*<<< orphan*/  flush_light; int /*<<< orphan*/  max_ib_mtu; } ;

/* Variables and functions */
 int EINVAL ; 
 int IPOIB_CM_MTU (int /*<<< orphan*/ ) ; 
 int IPOIB_UD_MTU (int /*<<< orphan*/ ) ; 
 scalar_t__ ipoib_cm_admin_enabled (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_cm_max_mtu (struct ipoib_dev_priv*) ; 
 int ipoib_propagate_ifnet_mtu (struct ipoib_dev_priv*,int,int) ; 
 int /*<<< orphan*/  ipoib_warn (struct ipoib_dev_priv*,char*,int) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int min (int,int) ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
ipoib_change_mtu(struct ipoib_dev_priv *priv, int new_mtu, bool propagate)
{
	int error, prev_admin_mtu;

	/* dev->if_mtu > 2K ==> connected mode */
	if (ipoib_cm_admin_enabled(priv)) {
		if (new_mtu > IPOIB_CM_MTU(ipoib_cm_max_mtu(priv)))
			return -EINVAL;

		if (new_mtu > priv->mcast_mtu)
			ipoib_warn(priv, "mtu > %d will cause multicast packet drops.\n",
				   priv->mcast_mtu);

		return (ipoib_propagate_ifnet_mtu(priv, new_mtu, propagate));
	}

	if (new_mtu > IPOIB_UD_MTU(priv->max_ib_mtu))
		return -EINVAL;

	prev_admin_mtu = priv->admin_mtu;
	priv->admin_mtu = new_mtu;
	error = ipoib_propagate_ifnet_mtu(priv, min(priv->mcast_mtu,
	    priv->admin_mtu), propagate);
	if (error == 0) {
		/* check for MTU change to avoid infinite loop */
		if (prev_admin_mtu != new_mtu)
			queue_work(ipoib_workqueue, &priv->flush_light);
	} else
		priv->admin_mtu = prev_admin_mtu;
	return (error);
}