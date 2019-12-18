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
struct link_config {scalar_t__ requested_speed; int supported; scalar_t__ requested_aneg; int requested_fc; int requested_fec; } ;
struct port_info {struct link_config link_cfg; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_AUTO ; 
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int FEC_AUTO ; 
 int FEC_BASER_RS ; 
 int FEC_RS ; 
 int FW_PORT_CAP32_ANEG ; 
 int FW_PORT_CAP32_FC_RX ; 
 int FW_PORT_CAP32_FC_TX ; 
 int FW_PORT_CAP32_FEC_BASER_RS ; 
 int FW_PORT_CAP32_FEC_RS ; 
 int FW_PORT_CAP32_FORCE_PAUSE ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  PORT_LOCK_ASSERT_OWNED (struct port_info*) ; 
 int speed_to_fwcap (scalar_t__) ; 

__attribute__((used)) static int
fixup_link_config(struct port_info *pi)
{
	int n = 0;
	struct link_config *lc = &pi->link_cfg;
	uint32_t fwspeed;

	PORT_LOCK_ASSERT_OWNED(pi);

	/* Speed (when not autonegotiating) */
	if (lc->requested_speed != 0) {
		fwspeed = speed_to_fwcap(lc->requested_speed);
		if ((fwspeed & lc->supported) == 0) {
			n++;
			lc->requested_speed = 0;
		}
	}

	/* Link autonegotiation */
	MPASS(lc->requested_aneg == AUTONEG_ENABLE ||
	    lc->requested_aneg == AUTONEG_DISABLE ||
	    lc->requested_aneg == AUTONEG_AUTO);
	if (lc->requested_aneg == AUTONEG_ENABLE &&
	    !(lc->supported & FW_PORT_CAP32_ANEG)) {
		n++;
		lc->requested_aneg = AUTONEG_AUTO;
	}

	/* Flow control */
	MPASS((lc->requested_fc & ~(PAUSE_TX | PAUSE_RX | PAUSE_AUTONEG)) == 0);
	if (lc->requested_fc & PAUSE_TX &&
	    !(lc->supported & FW_PORT_CAP32_FC_TX)) {
		n++;
		lc->requested_fc &= ~PAUSE_TX;
	}
	if (lc->requested_fc & PAUSE_RX &&
	    !(lc->supported & FW_PORT_CAP32_FC_RX)) {
		n++;
		lc->requested_fc &= ~PAUSE_RX;
	}
	if (!(lc->requested_fc & PAUSE_AUTONEG) &&
	    !(lc->supported & FW_PORT_CAP32_FORCE_PAUSE)) {
		n++;
		lc->requested_fc |= PAUSE_AUTONEG;
	}

	/* FEC */
	if ((lc->requested_fec & FEC_RS &&
	    !(lc->supported & FW_PORT_CAP32_FEC_RS)) ||
	    (lc->requested_fec & FEC_BASER_RS &&
	    !(lc->supported & FW_PORT_CAP32_FEC_BASER_RS))) {
		n++;
		lc->requested_fec = FEC_AUTO;
	}

	return (n);
}