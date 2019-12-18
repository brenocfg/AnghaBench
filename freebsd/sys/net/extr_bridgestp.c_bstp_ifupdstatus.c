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
typedef  scalar_t__ uint32_t ;
struct ifnet {int (* if_ioctl ) (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int if_flags; } ;
struct ifmediareq {int ifm_status; int ifm_active; } ;
struct bstp_state {int dummy; } ;
struct bstp_port {int bp_flags; int bp_ptp_link; scalar_t__ bp_path_cost; scalar_t__ bp_role; scalar_t__ bp_protover; int bp_operedge; scalar_t__ bp_infois; int /*<<< orphan*/  bp_active; struct ifnet* bp_ifp; struct bstp_state* bp_bs; } ;
typedef  int /*<<< orphan*/  ifmr ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 scalar_t__ BSTP_INFO_DISABLED ; 
 int /*<<< orphan*/  BSTP_LOCK (struct bstp_state*) ; 
 int BSTP_PORT_ADMEDGE ; 
 int BSTP_PORT_AUTOPTP ; 
 int BSTP_PORT_PNDCOST ; 
 scalar_t__ BSTP_PROTO_RSTP ; 
 scalar_t__ BSTP_ROLE_DISABLED ; 
 int /*<<< orphan*/  BSTP_UNLOCK (struct bstp_state*) ; 
 int IFF_UP ; 
 int IFM_ACTIVE ; 
 int IFM_FDX ; 
 int /*<<< orphan*/  SIOCGIFMEDIA ; 
 int /*<<< orphan*/  bstp_assign_roles (struct bstp_state*) ; 
 scalar_t__ bstp_calc_path_cost (struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_disable_port (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  bstp_enable_port (struct bstp_state*,struct bstp_port*) ; 
 int /*<<< orphan*/  bzero (char*,int) ; 
 int stub1 (struct ifnet*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bstp_ifupdstatus(void *arg, int pending)
{
	struct bstp_port *bp = (struct bstp_port *)arg;
	struct bstp_state *bs = bp->bp_bs;
	struct ifnet *ifp = bp->bp_ifp;
	struct ifmediareq ifmr;
	int error, changed;

	if (!bp->bp_active)
		return;

	bzero((char *)&ifmr, sizeof(ifmr));
	error = (*ifp->if_ioctl)(ifp, SIOCGIFMEDIA, (caddr_t)&ifmr);

	BSTP_LOCK(bs);
	changed = 0;
	if ((error == 0) && (ifp->if_flags & IFF_UP)) {
		if (ifmr.ifm_status & IFM_ACTIVE) {
			/* A full-duplex link is assumed to be point to point */
			if (bp->bp_flags & BSTP_PORT_AUTOPTP) {
				int fdx;

				fdx = ifmr.ifm_active & IFM_FDX ? 1 : 0;
				if (bp->bp_ptp_link ^ fdx) {
					bp->bp_ptp_link = fdx;
					changed = 1;
				}
			}

			/* Calc the cost if the link was down previously */
			if (bp->bp_flags & BSTP_PORT_PNDCOST) {
				uint32_t cost;

				cost = bstp_calc_path_cost(bp);
				if (bp->bp_path_cost != cost) {
					bp->bp_path_cost = cost;
					changed = 1;
				}
				bp->bp_flags &= ~BSTP_PORT_PNDCOST;
			}

			if (bp->bp_role == BSTP_ROLE_DISABLED) {
				bstp_enable_port(bs, bp);
				changed = 1;
			}
		} else {
			if (bp->bp_role != BSTP_ROLE_DISABLED) {
				bstp_disable_port(bs, bp);
				changed = 1;
				if ((bp->bp_flags & BSTP_PORT_ADMEDGE) &&
				    bp->bp_protover == BSTP_PROTO_RSTP)
					bp->bp_operedge = 1;
			}
		}
	} else if (bp->bp_infois != BSTP_INFO_DISABLED) {
		bstp_disable_port(bs, bp);
		changed = 1;
	}
	if (changed)
		bstp_assign_roles(bs);
	BSTP_UNLOCK(bs);
}