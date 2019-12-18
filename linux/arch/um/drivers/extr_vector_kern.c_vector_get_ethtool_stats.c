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
typedef  int /*<<< orphan*/  u64 ;
struct vector_private {int /*<<< orphan*/  estats; } ;
struct vector_estats {int dummy; } ;
struct net_device {int dummy; } ;
struct ethtool_stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct vector_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static void vector_get_ethtool_stats(struct net_device *dev,
	struct ethtool_stats *estats,
	u64 *tmp_stats)
{
	struct vector_private *vp = netdev_priv(dev);

	memcpy(tmp_stats, &vp->estats, sizeof(struct vector_estats));
}