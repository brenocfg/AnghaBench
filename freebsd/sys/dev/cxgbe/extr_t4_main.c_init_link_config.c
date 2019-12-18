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
struct link_config {int requested_fc; int requested_fec; int /*<<< orphan*/  requested_aneg; scalar_t__ requested_speed; } ;
struct port_info {struct link_config link_cfg; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_AUTO ; 
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int FEC_AUTO ; 
 int FEC_BASER_RS ; 
 int FEC_NONE ; 
 int FEC_RS ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  PORT_LOCK_ASSERT_OWNED (struct port_info*) ; 
 int t4_autoneg ; 
 int t4_fec ; 
 int t4_pause_settings ; 

__attribute__((used)) static void
init_link_config(struct port_info *pi)
{
	struct link_config *lc = &pi->link_cfg;

	PORT_LOCK_ASSERT_OWNED(pi);

	lc->requested_speed = 0;

	if (t4_autoneg == 0)
		lc->requested_aneg = AUTONEG_DISABLE;
	else if (t4_autoneg == 1)
		lc->requested_aneg = AUTONEG_ENABLE;
	else
		lc->requested_aneg = AUTONEG_AUTO;

	lc->requested_fc = t4_pause_settings & (PAUSE_TX | PAUSE_RX |
	    PAUSE_AUTONEG);

	if (t4_fec == -1 || t4_fec & FEC_AUTO)
		lc->requested_fec = FEC_AUTO;
	else {
		lc->requested_fec = FEC_NONE;
		if (t4_fec & FEC_RS)
			lc->requested_fec |= FEC_RS;
		if (t4_fec & FEC_BASER_RS)
			lc->requested_fec |= FEC_BASER_RS;
	}
}