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
struct vector_private {int coalesce; } ;
struct net_device {int dummy; } ;
struct ethtool_coalesce {int tx_coalesce_usecs; } ;

/* Variables and functions */
 int HZ ; 
 struct vector_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int vector_set_coalesce(struct net_device *netdev,
					struct ethtool_coalesce *ec)
{
	struct vector_private *vp = netdev_priv(netdev);

	vp->coalesce = (ec->tx_coalesce_usecs * HZ) / 1000000;
	if (vp->coalesce == 0)
		vp->coalesce = 1;
	return 0;
}