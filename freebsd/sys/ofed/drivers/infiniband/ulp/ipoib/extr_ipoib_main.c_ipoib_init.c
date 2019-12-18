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
struct ipoib_dev_priv {int /*<<< orphan*/  flush_light; struct ifnet* dev; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  ipoib_open (struct ipoib_dev_priv*) ; 
 int /*<<< orphan*/  ipoib_workqueue ; 
 int /*<<< orphan*/  queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ipoib_init(void *arg)
{
	struct ifnet *dev;
	struct ipoib_dev_priv *priv;

	priv = arg;
	dev = priv->dev;
	if ((dev->if_drv_flags & IFF_DRV_RUNNING) == 0)
		ipoib_open(priv);
	queue_work(ipoib_workqueue, &priv->flush_light);
}