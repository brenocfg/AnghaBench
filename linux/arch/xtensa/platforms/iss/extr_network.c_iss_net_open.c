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
struct net_device {int dummy; } ;
struct TYPE_2__ {int (* open ) (struct iss_net_private*) ;} ;
struct iss_net_private {int /*<<< orphan*/  lock; scalar_t__ timer_val; int /*<<< orphan*/  timer; int /*<<< orphan*/  opened_list; TYPE_1__ tp; } ;

/* Variables and functions */
 scalar_t__ ISS_NET_TIMER_VALUE ; 
 int iss_net_rx (struct net_device*) ; 
 int /*<<< orphan*/  iss_net_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct iss_net_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netif_start_queue (struct net_device*) ; 
 int /*<<< orphan*/  opened ; 
 int /*<<< orphan*/  opened_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int stub1 (struct iss_net_private*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int iss_net_open(struct net_device *dev)
{
	struct iss_net_private *lp = netdev_priv(dev);
	int err;

	spin_lock_bh(&lp->lock);

	err = lp->tp.open(lp);
	if (err < 0)
		goto out;

	netif_start_queue(dev);

	/* clear buffer - it can happen that the host side of the interface
	 * is full when we get here. In this case, new data is never queued,
	 * SIGIOs never arrive, and the net never works.
	 */
	while ((err = iss_net_rx(dev)) > 0)
		;

	spin_unlock_bh(&lp->lock);
	spin_lock_bh(&opened_lock);
	list_add(&lp->opened_list, &opened);
	spin_unlock_bh(&opened_lock);
	spin_lock_bh(&lp->lock);

	timer_setup(&lp->timer, iss_net_timer, 0);
	lp->timer_val = ISS_NET_TIMER_VALUE;
	mod_timer(&lp->timer, jiffies + lp->timer_val);

out:
	spin_unlock_bh(&lp->lock);
	return err;
}