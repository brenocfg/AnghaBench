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
struct uml_net_private {scalar_t__ fd; } ;
struct uml_net {int /*<<< orphan*/  pdev; struct net_device* dev; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENODEV ; 
 struct uml_net* find_device (int) ; 
 struct uml_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_netdev (struct net_device*) ; 

__attribute__((used)) static int net_remove(int n, char **error_out)
{
	struct uml_net *device;
	struct net_device *dev;
	struct uml_net_private *lp;

	device = find_device(n);
	if (device == NULL)
		return -ENODEV;

	dev = device->dev;
	lp = netdev_priv(dev);
	if (lp->fd > 0)
		return -EBUSY;
	unregister_netdev(dev);
	platform_device_unregister(&device->pdev);

	return 0;
}