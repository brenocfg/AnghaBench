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
struct port_info {int rx_e_chan_map; } ;

/* Variables and functions */

int
tnl_cong(struct port_info *pi, int drop)
{

	if (drop == -1)
		return (-1);
	else if (drop == 1)
		return (0);
	else
		return (pi->rx_e_chan_map);
}