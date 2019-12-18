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
struct bwn_mac {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_AFE_DDFS ; 
 int /*<<< orphan*/  BWN_PHY_LP_PHY_CTL ; 
 int /*<<< orphan*/  BWN_PHY_MASK (struct bwn_mac*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bwn_phy_lp_ddfs_turnoff(struct bwn_mac *mac)
{

	BWN_PHY_MASK(mac, BWN_PHY_AFE_DDFS, 0xfffd);
	BWN_PHY_MASK(mac, BWN_PHY_LP_PHY_CTL, 0xffdf);
}