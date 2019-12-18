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
struct link_config {unsigned int requested_fc; int supported; int advertising; scalar_t__ autoneg; int speed; int requested_speed; int duplex; int requested_duplex; unsigned char fc; scalar_t__ link_ok; } ;
struct cphy {TYPE_1__* ops; int /*<<< orphan*/  adapter; } ;
struct cmac {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* reset ) (struct cphy*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* autoneg_enable ) (struct cphy*) ;int /*<<< orphan*/  (* power_down ) (struct cphy*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* set_speed_duplex ) (struct cphy*,int,int) ;int /*<<< orphan*/  (* advertise ) (struct cphy*,int) ;} ;

/* Variables and functions */
 int ADVERTISED_Asym_Pause ; 
 int ADVERTISED_Pause ; 
 scalar_t__ AUTONEG_DISABLE ; 
 unsigned int PAUSE_RX ; 
 unsigned int PAUSE_TX ; 
 int SUPPORTED_Autoneg ; 
 int /*<<< orphan*/  is_10G (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct cphy*,int) ; 
 int /*<<< orphan*/  stub2 (struct cphy*,int,int) ; 
 int /*<<< orphan*/  stub3 (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct cphy*) ; 
 int /*<<< orphan*/  stub5 (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_mac_set_speed_duplex_fc (struct cmac*,int,int,unsigned int) ; 

int t3_link_start(struct cphy *phy, struct cmac *mac, struct link_config *lc)
{
	unsigned int fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	lc->link_ok = 0;
	if (lc->supported & SUPPORTED_Autoneg) {
		lc->advertising &= ~(ADVERTISED_Asym_Pause | ADVERTISED_Pause);
		if (fc) {
			lc->advertising |= ADVERTISED_Asym_Pause;
			if (fc & PAUSE_RX)
				lc->advertising |= ADVERTISED_Pause;
		}

		phy->ops->advertise(phy, lc->advertising);

		if (lc->autoneg == AUTONEG_DISABLE) {
			lc->speed = lc->requested_speed;
			lc->duplex = lc->requested_duplex;
			lc->fc = (unsigned char)fc;
			t3_mac_set_speed_duplex_fc(mac, lc->speed, lc->duplex,
						   fc);
			/* Also disables autoneg */
			phy->ops->set_speed_duplex(phy, lc->speed, lc->duplex);
			/* PR 5666. Power phy up when doing an ifup */
			if (!is_10G(phy->adapter))
				phy->ops->power_down(phy, 0);
		} else
			phy->ops->autoneg_enable(phy);
	} else {
		t3_mac_set_speed_duplex_fc(mac, -1, -1, fc);
		lc->fc = (unsigned char)fc;
		phy->ops->reset(phy, 0);
	}
	return 0;
}