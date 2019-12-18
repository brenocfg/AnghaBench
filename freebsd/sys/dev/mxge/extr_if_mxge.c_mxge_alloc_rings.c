#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int rx_ring_size; int num_slices; int /*<<< orphan*/ * ss; TYPE_1__* ifp; int /*<<< orphan*/  dev; } ;
typedef  TYPE_2__ mxge_softc_t ;
struct TYPE_12__ {int data0; } ;
typedef  TYPE_3__ mxge_cmd_t ;
typedef  int /*<<< orphan*/  mcp_kreq_ether_send_t ;
typedef  int /*<<< orphan*/  mcp_dma_addr_t ;
struct TYPE_13__ {int /*<<< orphan*/  ifq_maxlen; int /*<<< orphan*/  ifq_drv_maxlen; } ;
struct TYPE_10__ {TYPE_8__ if_snd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFQ_SET_MAXLEN (TYPE_8__*,int) ; 
 int /*<<< orphan*/  IFQ_SET_READY (TYPE_8__*) ; 
 int /*<<< orphan*/  MXGEFW_CMD_GET_SEND_RING_SIZE ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int mxge_alloc_slice_rings (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  mxge_free_rings (TYPE_2__*) ; 
 int mxge_send_cmd (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static int
mxge_alloc_rings(mxge_softc_t *sc)
{
	mxge_cmd_t cmd;
	int tx_ring_size;
	int tx_ring_entries, rx_ring_entries;
	int err, slice;
	
	/* get ring sizes */
	err = mxge_send_cmd(sc, MXGEFW_CMD_GET_SEND_RING_SIZE, &cmd);
	tx_ring_size = cmd.data0;
	if (err != 0) {
		device_printf(sc->dev, "Cannot determine tx ring sizes\n");
		goto abort;
	}

	tx_ring_entries = tx_ring_size / sizeof (mcp_kreq_ether_send_t);
	rx_ring_entries = sc->rx_ring_size / sizeof (mcp_dma_addr_t);
	IFQ_SET_MAXLEN(&sc->ifp->if_snd, tx_ring_entries - 1);
	sc->ifp->if_snd.ifq_drv_maxlen = sc->ifp->if_snd.ifq_maxlen;
	IFQ_SET_READY(&sc->ifp->if_snd);

	for (slice = 0; slice < sc->num_slices; slice++) {
		err = mxge_alloc_slice_rings(&sc->ss[slice],
					     rx_ring_entries,
					     tx_ring_entries);
		if (err != 0)
			goto abort;
	}
	return 0;

abort:
	mxge_free_rings(sc);
	return err;

}