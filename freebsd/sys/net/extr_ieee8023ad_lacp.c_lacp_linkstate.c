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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;
typedef  int u_int ;
struct lagg_port {struct ifnet* lp_ifp; } ;
struct lacp_softc {int dummy; } ;
struct lacp_port {int lp_media; scalar_t__ lp_state; scalar_t__ lp_key; int /*<<< orphan*/  lp_selected; struct lacp_softc* lp_lsc; } ;
struct ifnet {int (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;scalar_t__ if_link_state; } ;
struct ifmediareq {int ifm_active; } ;
typedef  int /*<<< orphan*/  ifmr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ IFM_ETHER ; 
 int IFM_FDX ; 
 scalar_t__ IFM_TYPE (int) ; 
 int /*<<< orphan*/  LACP_DPRINTF (struct lacp_port*) ; 
 int /*<<< orphan*/  LACP_LOCK (struct lacp_softc*) ; 
 struct lacp_port* LACP_PORT (struct lagg_port*) ; 
 int /*<<< orphan*/  LACP_UNLOCK (struct lacp_softc*) ; 
 int /*<<< orphan*/  LACP_UNSELECTED ; 
 scalar_t__ LINK_STATE_UP ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  SIOCGIFXMEDIA ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 scalar_t__ lacp_compose_key (struct lacp_port*) ; 
 int /*<<< orphan*/  lacp_port_disable (struct lacp_port*) ; 
 int /*<<< orphan*/  lacp_port_enable (struct lacp_port*) ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub2 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
lacp_linkstate(struct lagg_port *lgp)
{
	struct lacp_port *lp = LACP_PORT(lgp);
	struct lacp_softc *lsc = lp->lp_lsc;
	struct ifnet *ifp = lgp->lp_ifp;
	struct ifmediareq ifmr;
	int error = 0;
	u_int media;
	uint8_t old_state;
	uint16_t old_key;

	bzero((char *)&ifmr, sizeof(ifmr));
	error = (*ifp->if_ioctl)(ifp, SIOCGIFXMEDIA, (caddr_t)&ifmr);
	if (error != 0) {
		bzero((char *)&ifmr, sizeof(ifmr));
		error = (*ifp->if_ioctl)(ifp, SIOCGIFMEDIA, (caddr_t)&ifmr);
	}
	if (error != 0)
		return;

	LACP_LOCK(lsc);
	media = ifmr.ifm_active;
	LACP_DPRINTF((lp, "media changed 0x%x -> 0x%x, ether = %d, fdx = %d, "
	    "link = %d\n", lp->lp_media, media, IFM_TYPE(media) == IFM_ETHER,
	    (media & IFM_FDX) != 0, ifp->if_link_state == LINK_STATE_UP));
	old_state = lp->lp_state;
	old_key = lp->lp_key;

	lp->lp_media = media;
	/*
	 * If the port is not an active full duplex Ethernet link then it can
	 * not be aggregated.
	 */
	if (IFM_TYPE(media) != IFM_ETHER || (media & IFM_FDX) == 0 ||
	    ifp->if_link_state != LINK_STATE_UP) {
		lacp_port_disable(lp);
	} else {
		lacp_port_enable(lp);
	}
	lp->lp_key = lacp_compose_key(lp);

	if (old_state != lp->lp_state || old_key != lp->lp_key) {
		LACP_DPRINTF((lp, "-> UNSELECTED\n"));
		lp->lp_selected = LACP_UNSELECTED;
	}
	LACP_UNLOCK(lsc);
}