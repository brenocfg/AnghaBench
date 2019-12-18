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
struct vi_info {struct port_info* pi; } ;
struct link_config {int supported; int requested_speed; int /*<<< orphan*/  requested_fc; int /*<<< orphan*/  requested_aneg; } ;
struct ifmedia {int /*<<< orphan*/  ifm_media; } ;
struct port_info {scalar_t__ up_vis; struct adapter* adapter; struct link_config link_cfg; struct ifmedia media; } ;
struct ifnet {struct vi_info* if_softc; } ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTONEG_DISABLE ; 
 int /*<<< orphan*/  AUTONEG_ENABLE ; 
 int ENOTSUP ; 
 int FW_PORT_CAP32_ANEG ; 
 scalar_t__ IFM_AUTO ; 
 int IFM_ETH_RXPAUSE ; 
 int IFM_ETH_TXPAUSE ; 
 int IFM_OPTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ IFM_SUBTYPE (int /*<<< orphan*/ ) ; 
 int INTR_OK ; 
 int /*<<< orphan*/  PAUSE_AUTONEG ; 
 int /*<<< orphan*/  PAUSE_RX ; 
 int /*<<< orphan*/  PAUSE_TX ; 
 int /*<<< orphan*/  PORT_LOCK (struct port_info*) ; 
 int /*<<< orphan*/  PORT_UNLOCK (struct port_info*) ; 
 int SLEEP_OK ; 
 int apply_link_config (struct port_info*) ; 
 int begin_synchronized_op (struct adapter*,int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  end_synchronized_op (struct adapter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fixup_link_config (struct port_info*) ; 
 int ifmedia_baudrate (int /*<<< orphan*/ ) ; 

int
cxgbe_media_change(struct ifnet *ifp)
{
	struct vi_info *vi = ifp->if_softc;
	struct port_info *pi = vi->pi;
	struct ifmedia *ifm = &pi->media;
	struct link_config *lc = &pi->link_cfg;
	struct adapter *sc = pi->adapter;
	int rc;

	rc = begin_synchronized_op(sc, NULL, SLEEP_OK | INTR_OK, "t4mec");
	if (rc != 0)
		return (rc);
	PORT_LOCK(pi);
	if (IFM_SUBTYPE(ifm->ifm_media) == IFM_AUTO) {
		/* ifconfig .. media autoselect */
		if (!(lc->supported & FW_PORT_CAP32_ANEG)) {
			rc = ENOTSUP; /* AN not supported by transceiver */
			goto done;
		}
		lc->requested_aneg = AUTONEG_ENABLE;
		lc->requested_speed = 0;
		lc->requested_fc |= PAUSE_AUTONEG;
	} else {
		lc->requested_aneg = AUTONEG_DISABLE;
		lc->requested_speed =
		    ifmedia_baudrate(ifm->ifm_media) / 1000000;
		lc->requested_fc = 0;
		if (IFM_OPTIONS(ifm->ifm_media) & IFM_ETH_RXPAUSE)
			lc->requested_fc |= PAUSE_RX;
		if (IFM_OPTIONS(ifm->ifm_media) & IFM_ETH_TXPAUSE)
			lc->requested_fc |= PAUSE_TX;
	}
	if (pi->up_vis > 0) {
		fixup_link_config(pi);
		rc = apply_link_config(pi);
	}
done:
	PORT_UNLOCK(pi);
	end_synchronized_op(sc, 0);
	return (rc);
}