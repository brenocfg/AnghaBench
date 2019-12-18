#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* iflib_rxq_t ;
typedef  TYPE_3__* iflib_fl_t ;
typedef  TYPE_4__* if_ctx_t ;
struct TYPE_12__ {scalar_t__ ifc_rx_mbuf_sz; scalar_t__ ifc_max_fl_buf_size; } ;
struct TYPE_11__ {scalar_t__ ifl_credits; scalar_t__ ifl_buf_size; TYPE_1__* ifl_ifdi; scalar_t__ ifl_size; int /*<<< orphan*/  ifl_zone; int /*<<< orphan*/  ifl_cltype; int /*<<< orphan*/  ifl_rx_bitmap; TYPE_2__* ifl_rxq; } ;
struct TYPE_10__ {TYPE_4__* ifr_ctx; } ;
struct TYPE_9__ {int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  _iflib_fl_refill (TYPE_4__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  bit_nclear (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  iflib_fl_bufs_free (TYPE_3__*) ; 
 int /*<<< orphan*/  m_gettype (scalar_t__) ; 
 int /*<<< orphan*/  m_getzone (scalar_t__) ; 
 scalar_t__ min (int,scalar_t__) ; 

__attribute__((used)) static int
iflib_fl_setup(iflib_fl_t fl)
{
	iflib_rxq_t rxq = fl->ifl_rxq;
	if_ctx_t ctx = rxq->ifr_ctx;

	bit_nclear(fl->ifl_rx_bitmap, 0, fl->ifl_size - 1);
	/*
	** Free current RX buffer structs and their mbufs
	*/
	iflib_fl_bufs_free(fl);
	/* Now replenish the mbufs */
	MPASS(fl->ifl_credits == 0);
	fl->ifl_buf_size = ctx->ifc_rx_mbuf_sz;
	if (fl->ifl_buf_size > ctx->ifc_max_fl_buf_size)
		ctx->ifc_max_fl_buf_size = fl->ifl_buf_size;
	fl->ifl_cltype = m_gettype(fl->ifl_buf_size);
	fl->ifl_zone = m_getzone(fl->ifl_buf_size);


	/* avoid pre-allocating zillions of clusters to an idle card
	 * potentially speeding up attach
	 */
	_iflib_fl_refill(ctx, fl, min(128, fl->ifl_size));
	MPASS(min(128, fl->ifl_size) == fl->ifl_credits);
	if (min(128, fl->ifl_size) != fl->ifl_credits)
		return (ENOBUFS);
	/*
	 * handle failure
	 */
	MPASS(rxq != NULL);
	MPASS(fl->ifl_ifdi != NULL);
	bus_dmamap_sync(fl->ifl_ifdi->idi_tag, fl->ifl_ifdi->idi_map,
	    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
	return (0);
}