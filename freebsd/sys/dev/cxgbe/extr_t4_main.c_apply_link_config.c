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
struct link_config {scalar_t__ requested_aneg; int supported; int requested_fc; int requested_fec; int fc; scalar_t__ link_ok; } ;
struct port_info {int /*<<< orphan*/  dev; int /*<<< orphan*/  tx_chan; struct link_config link_cfg; struct adapter* adapter; } ;
struct adapter {int flags; int /*<<< orphan*/  mbox; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_SYNCHRONIZED_OP (struct adapter*) ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int FEC_BASER_RS ; 
 int FEC_RS ; 
 int FW_EPERM ; 
 int FW_PORT_CAP32_ANEG ; 
 int FW_PORT_CAP32_FC_RX ; 
 int FW_PORT_CAP32_FC_TX ; 
 int FW_PORT_CAP32_FEC_BASER_RS ; 
 int FW_PORT_CAP32_FEC_RS ; 
 int FW_PORT_CAP32_FORCE_PAUSE ; 
 int IS_VF ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int /*<<< orphan*/  PORT_LOCK_ASSERT_OWNED (struct port_info*) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int t4_link_l1cfg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct link_config*) ; 

__attribute__((used)) static int
apply_link_config(struct port_info *pi)
{
	struct adapter *sc = pi->adapter;
	struct link_config *lc = &pi->link_cfg;
	int rc;

#ifdef INVARIANTS
	ASSERT_SYNCHRONIZED_OP(sc);
	PORT_LOCK_ASSERT_OWNED(pi);

	if (lc->requested_aneg == AUTONEG_ENABLE)
		MPASS(lc->supported & FW_PORT_CAP32_ANEG);
	if (!(lc->requested_fc & PAUSE_AUTONEG))
		MPASS(lc->supported & FW_PORT_CAP32_FORCE_PAUSE);
	if (lc->requested_fc & PAUSE_TX)
		MPASS(lc->supported & FW_PORT_CAP32_FC_TX);
	if (lc->requested_fc & PAUSE_RX)
		MPASS(lc->supported & FW_PORT_CAP32_FC_RX);
	if (lc->requested_fec & FEC_RS)
		MPASS(lc->supported & FW_PORT_CAP32_FEC_RS);
	if (lc->requested_fec & FEC_BASER_RS)
		MPASS(lc->supported & FW_PORT_CAP32_FEC_BASER_RS);
#endif
	rc = -t4_link_l1cfg(sc, sc->mbox, pi->tx_chan, lc);
	if (rc != 0) {
		/* Don't complain if the VF driver gets back an EPERM. */
		if (!(sc->flags & IS_VF) || rc != FW_EPERM)
			device_printf(pi->dev, "l1cfg failed: %d\n", rc);
	} else {
		/*
		 * An L1_CFG will almost always result in a link-change event if
		 * the link is up, and the driver will refresh the actual
		 * fec/fc/etc. when the notification is processed.  If the link
		 * is down then the actual settings are meaningless.
		 *
		 * This takes care of the case where a change in the L1 settings
		 * may not result in a notification.
		 */
		if (lc->link_ok && !(lc->requested_fc & PAUSE_AUTONEG))
			lc->fc = lc->requested_fc & (PAUSE_TX | PAUSE_RX);
	}
	return (rc);
}