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
struct phy_device {struct net_device* attached_dev; } ;
struct net_device {int /*<<< orphan*/  priv_flags; int /*<<< orphan*/  features; int /*<<< orphan*/ * eth_mangle_tx; int /*<<< orphan*/ * eth_mangle_rx; int /*<<< orphan*/ * phy_ptr; } ;
struct mvswitch_priv {int /*<<< orphan*/  orig_features; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFF_NO_IP_ALIGN ; 
 struct mvswitch_priv* to_mvsw (struct phy_device*) ; 

__attribute__((used)) static void
mvswitch_detach(struct phy_device *pdev)
{
	struct mvswitch_priv *priv = to_mvsw(pdev);
	struct net_device *dev = pdev->attached_dev;

	if (!dev)
		return;

	dev->phy_ptr = NULL;
	dev->eth_mangle_rx = NULL;
	dev->eth_mangle_tx = NULL;
	dev->features = priv->orig_features;
	dev->priv_flags &= ~IFF_NO_IP_ALIGN;
}