#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct ifbropreq {int ifbop_maxage; int ifbop_hellotime; int ifbop_fwddelay; TYPE_4__ ifbop_last_tc_time; int /*<<< orphan*/  ifbop_designated_bridge; int /*<<< orphan*/  ifbop_designated_root; int /*<<< orphan*/  ifbop_bridgeid; int /*<<< orphan*/  ifbop_root_path_cost; int /*<<< orphan*/  ifbop_protocol; int /*<<< orphan*/  ifbop_priority; int /*<<< orphan*/  ifbop_holdcount; scalar_t__ ifbop_root_port; } ;
struct TYPE_10__ {int /*<<< orphan*/  tv_usec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_8__ {int /*<<< orphan*/  pv_dbridge_id; int /*<<< orphan*/  pv_root_id; int /*<<< orphan*/  pv_cost; } ;
struct TYPE_7__ {int /*<<< orphan*/  pv_dbridge_id; } ;
struct bstp_state {int bs_bridge_max_age; int bs_bridge_htime; int bs_bridge_fdelay; TYPE_5__ bs_last_tc_time; TYPE_3__ bs_root_pv; TYPE_2__ bs_bridge_pv; int /*<<< orphan*/  bs_protover; int /*<<< orphan*/  bs_bridge_priority; int /*<<< orphan*/  bs_txholdcount; struct bstp_port* bs_root_port; } ;
struct bstp_port {TYPE_1__* bp_ifp; } ;
struct bridge_softc {struct bstp_state sc_stp; } ;
struct TYPE_6__ {scalar_t__ if_index; } ;

/* Variables and functions */

__attribute__((used)) static int
bridge_ioctl_gbparam(struct bridge_softc *sc, void *arg)
{
	struct ifbropreq *req = arg;
	struct bstp_state *bs = &sc->sc_stp;
	struct bstp_port *root_port;

	req->ifbop_maxage = bs->bs_bridge_max_age >> 8;
	req->ifbop_hellotime = bs->bs_bridge_htime >> 8;
	req->ifbop_fwddelay = bs->bs_bridge_fdelay >> 8;

	root_port = bs->bs_root_port;
	if (root_port == NULL)
		req->ifbop_root_port = 0;
	else
		req->ifbop_root_port = root_port->bp_ifp->if_index;

	req->ifbop_holdcount = bs->bs_txholdcount;
	req->ifbop_priority = bs->bs_bridge_priority;
	req->ifbop_protocol = bs->bs_protover;
	req->ifbop_root_path_cost = bs->bs_root_pv.pv_cost;
	req->ifbop_bridgeid = bs->bs_bridge_pv.pv_dbridge_id;
	req->ifbop_designated_root = bs->bs_root_pv.pv_root_id;
	req->ifbop_designated_bridge = bs->bs_root_pv.pv_dbridge_id;
	req->ifbop_last_tc_time.tv_sec = bs->bs_last_tc_time.tv_sec;
	req->ifbop_last_tc_time.tv_usec = bs->bs_last_tc_time.tv_usec;

	return (0);
}