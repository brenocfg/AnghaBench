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
typedef  scalar_t__ uint8_t ;
struct bwn_phy_lp {int plp_crsusr_off; int plp_crssys_off; } ;
struct TYPE_2__ {struct bwn_phy_lp phy_lp; } ;
struct bwn_mac {TYPE_1__ mac_phy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BWN_PHY_CRSGAIN_CTL ; 
 int /*<<< orphan*/  BWN_PHY_SETMASK (struct bwn_mac*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void
bwn_phy_lp_set_deaf(struct bwn_mac *mac, uint8_t user)
{
	struct bwn_phy_lp *plp = &mac->mac_phy.phy_lp;

	if (user)
		plp->plp_crsusr_off = 1;
	else
		plp->plp_crssys_off = 1;

	BWN_PHY_SETMASK(mac, BWN_PHY_CRSGAIN_CTL, 0xff1f, 0x80);
}