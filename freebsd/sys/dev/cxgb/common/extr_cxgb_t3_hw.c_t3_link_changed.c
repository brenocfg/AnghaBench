#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct link_config {int link_ok; int speed; int duplex; int fc; int requested_fc; scalar_t__ autoneg; } ;
struct TYPE_15__ {int /*<<< orphan*/  link_faults; } ;
struct cmac {scalar_t__ was_reset; scalar_t__ offset; TYPE_2__ stats; } ;
struct cphy {int rst; TYPE_1__* ops; } ;
struct port_info {scalar_t__ link_fault; int /*<<< orphan*/  port_id; struct link_config link_config; struct cmac mac; struct cphy phy; } ;
struct TYPE_16__ {int nports; scalar_t__ rev; } ;
struct TYPE_17__ {TYPE_3__ params; } ;
typedef  TYPE_4__ adapter_t ;
struct TYPE_14__ {int /*<<< orphan*/  (* reset ) (struct cphy*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* get_link_status ) (struct cphy*,int*,int*,int*,int*) ;} ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 scalar_t__ A_XGM_INT_ENABLE ; 
 scalar_t__ A_XGM_RX_CTRL ; 
 scalar_t__ A_XGM_STAT_CTRL ; 
 scalar_t__ A_XGM_TXFIFO_CFG ; 
 scalar_t__ A_XGM_TX_CTRL ; 
 scalar_t__ A_XGM_XAUI_ACT_CTRL ; 
 int DUPLEX_INVALID ; 
 int F_CLRSTATS ; 
 int F_ENDROPPKT ; 
 int F_RXEN ; 
 int F_TXACTENABLE ; 
 int F_TXEN ; 
 int F_XGM_INT ; 
 scalar_t__ LF_MAYBE ; 
 void* LF_NO ; 
 scalar_t__ LF_YES ; 
 int MAC_DIRECTION_RX ; 
 int MAC_DIRECTION_TX ; 
 int PAUSE_AUTONEG ; 
 int PAUSE_RX ; 
 int PAUSE_TX ; 
 int PHY_LINK_PARTIAL ; 
 int PHY_LINK_UP ; 
 int SPEED_INVALID ; 
 scalar_t__ T3_REV_C ; 
 struct port_info* adap2pinfo (TYPE_4__*,int) ; 
 int /*<<< orphan*/  stub1 (struct cphy*,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  stub2 (struct cphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3_clear_faults (TYPE_4__*,int) ; 
 int t3_detect_link_fault (TYPE_4__*,int) ; 
 int /*<<< orphan*/  t3_mac_disable (struct cmac*,int) ; 
 int /*<<< orphan*/  t3_mac_enable (struct cmac*,int) ; 
 int /*<<< orphan*/  t3_mac_set_speed_duplex_fc (struct cmac*,int,int,int) ; 
 int /*<<< orphan*/  t3_os_link_changed (TYPE_4__*,int,int,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  t3_set_reg_field (TYPE_4__*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (TYPE_4__*,scalar_t__,int) ; 
 int /*<<< orphan*/  t3_xgm_intr_disable (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t3b_pcs_reset (struct cmac*) ; 
 int /*<<< orphan*/  t3c_pcs_force_los (struct cmac*) ; 
 scalar_t__ uses_xaui (TYPE_4__*) ; 

void t3_link_changed(adapter_t *adapter, int port_id)
{
	int link_ok, speed, duplex, fc, link_fault, link_state;
	struct port_info *pi = adap2pinfo(adapter, port_id);
	struct cphy *phy = &pi->phy;
	struct cmac *mac = &pi->mac;
	struct link_config *lc = &pi->link_config;

	link_ok = lc->link_ok;
	speed = lc->speed;
	duplex = lc->duplex;
	fc = lc->fc;
	link_fault = 0;

	phy->ops->get_link_status(phy, &link_state, &speed, &duplex, &fc);
	link_ok = (link_state == PHY_LINK_UP);
	if (link_state != PHY_LINK_PARTIAL)
		phy->rst = 0;
	else if (++phy->rst == 3) {
		phy->ops->reset(phy, 0);
		phy->rst = 0;
	}

	if (link_ok == 0)
		pi->link_fault = LF_NO;

	if (lc->requested_fc & PAUSE_AUTONEG)
		fc &= lc->requested_fc;
	else
		fc = lc->requested_fc & (PAUSE_RX | PAUSE_TX);

	/* Update mac speed before checking for link fault. */
	if (link_ok && speed >= 0 && lc->autoneg == AUTONEG_ENABLE &&
	    (speed != lc->speed || duplex != lc->duplex || fc != lc->fc))
		t3_mac_set_speed_duplex_fc(mac, speed, duplex, fc);

	/*
	 * Check for link faults if any of these is true:
	 * a) A link fault is suspected, and PHY says link ok
	 * b) PHY link transitioned from down -> up
	 */
	if (adapter->params.nports <= 2 &&
	    ((pi->link_fault && link_ok) || (!lc->link_ok && link_ok))) {

		link_fault = t3_detect_link_fault(adapter, port_id);
		if (link_fault) {
			if (pi->link_fault != LF_YES) {
				mac->stats.link_faults++;
				pi->link_fault = LF_YES;
			}

			if (uses_xaui(adapter)) {
				if (adapter->params.rev >= T3_REV_C)
					t3c_pcs_force_los(mac);
				else
					t3b_pcs_reset(mac);
			}

			/* Don't report link up */
			link_ok = 0;
		} else {
			/* clear faults here if this was a false alarm. */
			if (pi->link_fault == LF_MAYBE &&
			    link_ok && lc->link_ok)
				t3_clear_faults(adapter, port_id);

			pi->link_fault = LF_NO;
		}
	}

	if (link_ok == lc->link_ok && speed == lc->speed &&
	    duplex == lc->duplex && fc == lc->fc)
		return;                            /* nothing changed */

	lc->link_ok = (unsigned char)link_ok;
	lc->speed = speed < 0 ? SPEED_INVALID : speed;
	lc->duplex = duplex < 0 ? DUPLEX_INVALID : duplex;
	lc->fc = fc;

	if (link_ok) {

		/* down -> up, or up -> up with changed settings */

		if (adapter->params.rev > 0 && uses_xaui(adapter)) {

			if (adapter->params.rev >= T3_REV_C)
				t3c_pcs_force_los(mac);
			else
				t3b_pcs_reset(mac);

			t3_write_reg(adapter, A_XGM_XAUI_ACT_CTRL + mac->offset,
				     F_TXACTENABLE | F_RXEN);
		}

		/* disable TX FIFO drain */
		t3_set_reg_field(adapter, A_XGM_TXFIFO_CFG + mac->offset,
				 F_ENDROPPKT, 0);

		t3_mac_enable(mac, MAC_DIRECTION_TX | MAC_DIRECTION_RX);
		t3_set_reg_field(adapter, A_XGM_STAT_CTRL + mac->offset,
				 F_CLRSTATS, 1);
		t3_clear_faults(adapter, port_id);

	} else {

		/* up -> down */

		if (adapter->params.rev > 0 && uses_xaui(adapter)) {
			t3_write_reg(adapter,
				     A_XGM_XAUI_ACT_CTRL + mac->offset, 0);
		}

		t3_xgm_intr_disable(adapter, pi->port_id);
		if (adapter->params.nports <= 2) {
			t3_set_reg_field(adapter,
					 A_XGM_INT_ENABLE + mac->offset,
					 F_XGM_INT, 0);

			t3_mac_disable(mac, MAC_DIRECTION_RX);

			/*
			 * Make sure Tx FIFO continues to drain, even as rxen is
			 * left high to help detect and indicate remote faults.
			 */
			t3_set_reg_field(adapter,
			    A_XGM_TXFIFO_CFG + mac->offset, 0, F_ENDROPPKT);
			t3_write_reg(adapter, A_XGM_RX_CTRL + mac->offset, 0);
			t3_write_reg(adapter,
			    A_XGM_TX_CTRL + mac->offset, F_TXEN);
			t3_write_reg(adapter,
			    A_XGM_RX_CTRL + mac->offset, F_RXEN);
		}
	}

	t3_os_link_changed(adapter, port_id, link_ok, speed, duplex, fc,
	    mac->was_reset);
	mac->was_reset = 0;
}