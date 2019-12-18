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
struct net_device {int watchdog_timeo; int flags; int /*<<< orphan*/ * ethtool_ops; int /*<<< orphan*/  tx_queue_len; int /*<<< orphan*/  type; int /*<<< orphan*/  hard_header_len; int /*<<< orphan*/  addr_len; int /*<<< orphan*/  features; int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/ * header_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_IEEE1394 ; 
 int /*<<< orphan*/  FWNET_ALEN ; 
 int /*<<< orphan*/  FWNET_HLEN ; 
 int /*<<< orphan*/  FWNET_TX_QUEUE_LEN ; 
 int HZ ; 
 int IFF_BROADCAST ; 
 int IFF_MULTICAST ; 
 int /*<<< orphan*/  NETIF_F_HIGHDMA ; 
 int /*<<< orphan*/  fwnet_ethtool_ops ; 
 int /*<<< orphan*/  fwnet_header_ops ; 
 int /*<<< orphan*/  fwnet_netdev_ops ; 

__attribute__((used)) static void fwnet_init_dev(struct net_device *net)
{
	net->header_ops		= &fwnet_header_ops;
	net->netdev_ops		= &fwnet_netdev_ops;
	net->watchdog_timeo	= 2 * HZ;
	net->flags		= IFF_BROADCAST | IFF_MULTICAST;
	net->features		= NETIF_F_HIGHDMA;
	net->addr_len		= FWNET_ALEN;
	net->hard_header_len	= FWNET_HLEN;
	net->type		= ARPHRD_IEEE1394;
	net->tx_queue_len	= FWNET_TX_QUEUE_LEN;
	net->ethtool_ops	= &fwnet_ethtool_ops;
}