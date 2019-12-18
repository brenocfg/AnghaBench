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
typedef  int uint32_t ;
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  bwn_phy_g_switch_chan (struct bwn_mac*,int,int /*<<< orphan*/ ) ; 

int
bwn_phy_g_switch_channel(struct bwn_mac *mac, uint32_t newchan)
{

	if ((newchan < 1) || (newchan > 14))
		return (EINVAL);
	bwn_phy_g_switch_chan(mac, newchan, 0);

	return (0);
}