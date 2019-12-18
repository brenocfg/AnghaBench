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
struct ifnet {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_ETHTOOL_OPS (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ipoib_ethtool_ops ; 

void ipoib_set_ethtool_ops(struct ifnet *dev)
{
	SET_ETHTOOL_OPS(dev, &ipoib_ethtool_ops);
}