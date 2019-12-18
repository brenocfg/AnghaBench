#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct net_device {int dummy; } ;
struct chtls_dev {struct net_device** ports; } ;
struct TYPE_2__ {int /*<<< orphan*/  inet_rcv_saddr; } ;

/* Variables and functions */
 TYPE_1__* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  init_net ; 
 struct net_device* ip_dev_find (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_vlan_dev (struct net_device*) ; 
 scalar_t__ likely (int) ; 
 struct net_device* vlan_dev_real_dev (struct net_device*) ; 

__attribute__((used)) static struct net_device *chtls_ipv4_netdev(struct chtls_dev *cdev,
					    struct sock *sk)
{
	struct net_device *ndev = cdev->ports[0];

	if (likely(!inet_sk(sk)->inet_rcv_saddr))
		return ndev;

	ndev = ip_dev_find(&init_net, inet_sk(sk)->inet_rcv_saddr);
	if (!ndev)
		return NULL;

	if (is_vlan_dev(ndev))
		return vlan_dev_real_dev(ndev);
	return ndev;
}