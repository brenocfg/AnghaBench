#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct mxge_add_maddr_ctx {int error; TYPE_1__* sc; } ;
struct ifnet {int if_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; scalar_t__ adopted_rx_filter_bug; int /*<<< orphan*/  fw_multicast_support; struct ifnet* ifp; } ;
typedef  TYPE_1__ mxge_softc_t ;
typedef  int /*<<< orphan*/  mxge_cmd_t ;

/* Variables and functions */
 int IFF_ALLMULTI ; 
 int /*<<< orphan*/  MXGEFW_DISABLE_ALLMULTI ; 
 int /*<<< orphan*/  MXGEFW_ENABLE_ALLMULTI ; 
 int /*<<< orphan*/  MXGEFW_LEAVE_ALL_MULTICAST_GROUPS ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  if_foreach_llmaddr (struct ifnet*,int /*<<< orphan*/ ,struct mxge_add_maddr_ctx*) ; 
 int /*<<< orphan*/  mxge_add_maddr ; 
 int mxge_send_cmd (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mxge_set_multicast_list(mxge_softc_t *sc)
{
	struct mxge_add_maddr_ctx ctx;
	struct ifnet *ifp = sc->ifp;
	mxge_cmd_t cmd;
	int err;

	/* This firmware is known to not support multicast */
	if (!sc->fw_multicast_support)
		return;

	/* Disable multicast filtering while we play with the lists*/
	err = mxge_send_cmd(sc, MXGEFW_ENABLE_ALLMULTI, &cmd);
	if (err != 0) {
		device_printf(sc->dev, "Failed MXGEFW_ENABLE_ALLMULTI,"
		       " error status: %d\n", err);
		return;
	}
	
	if (sc->adopted_rx_filter_bug)
		return;
	
	if (ifp->if_flags & IFF_ALLMULTI)
		/* request to disable multicast filtering, so quit here */
		return;

	/* Flush all the filters */

	err = mxge_send_cmd(sc, MXGEFW_LEAVE_ALL_MULTICAST_GROUPS, &cmd);
	if (err != 0) {
		device_printf(sc->dev,
			      "Failed MXGEFW_LEAVE_ALL_MULTICAST_GROUPS"
			      ", error status: %d\n", err);
		return;
	}

	/* Walk the multicast list, and add each address */
	ctx.sc = sc;
	ctx.error = 0;
	if_foreach_llmaddr(ifp, mxge_add_maddr, &ctx);
	if (ctx.error != 0) {
		device_printf(sc->dev, "Failed MXGEFW_JOIN_MULTICAST_GROUP, "
		    "error status:" "%d\t", ctx.error);
		/* abort, leaving multicast filtering off */
		return;
	}

	/* Enable multicast filtering */
	err = mxge_send_cmd(sc, MXGEFW_DISABLE_ALLMULTI, &cmd);
	if (err != 0) {
		device_printf(sc->dev, "Failed MXGEFW_DISABLE_ALLMULTI"
		       ", error status: %d\n", err);
	}
}