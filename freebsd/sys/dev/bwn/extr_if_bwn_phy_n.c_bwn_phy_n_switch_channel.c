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
typedef  int /*<<< orphan*/  uint32_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int ENXIO ; 
 int bwn_nphy_op_switch_channel (struct bwn_mac*,int /*<<< orphan*/ ) ; 

int
bwn_phy_n_switch_channel(struct bwn_mac *mac, uint32_t newchan)
{
#ifdef	BWN_GPL_PHY
	return bwn_nphy_op_switch_channel(mac, newchan);
#else
	return (ENXIO);
#endif
}