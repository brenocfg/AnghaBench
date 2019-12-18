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
struct fe_priv {int /*<<< orphan*/  netdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  fe_speed_str (int) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,int,...) ; 

void mt7620_print_link_state(struct fe_priv *priv, int port, int link,
			     int speed, int duplex)
{
	if (link)
		netdev_info(priv->netdev, "port %d link up (%sMbps/%s duplex)\n",
			    port, fe_speed_str(speed),
			    (duplex) ? "Full" : "Half");
	else
		netdev_info(priv->netdev, "port %d link down\n", port);
}