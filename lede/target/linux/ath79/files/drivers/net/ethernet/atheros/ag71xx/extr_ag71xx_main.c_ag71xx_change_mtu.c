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
struct net_device {int mtu; } ;
struct ag71xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MAC_MFL ; 
 int /*<<< orphan*/  ag71xx_max_frame_len (int) ; 
 int /*<<< orphan*/  ag71xx_wr (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ag71xx* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int ag71xx_change_mtu(struct net_device *dev, int new_mtu)
{
	struct ag71xx *ag = netdev_priv(dev);

	dev->mtu = new_mtu;
	ag71xx_wr(ag, AG71XX_REG_MAC_MFL,
		  ag71xx_max_frame_len(dev->mtu));

	return 0;
}