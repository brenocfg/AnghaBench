#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u_int ;
typedef  int /*<<< orphan*/  qidx_t ;
typedef  TYPE_2__* iflib_rxq_t ;
typedef  TYPE_3__* iflib_fl_t ;
typedef  TYPE_4__* if_ctx_t ;
struct TYPE_10__ {int (* isc_rxd_available ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  ifc_softc; } ;
struct TYPE_9__ {TYPE_1__* ifl_ifdi; } ;
struct TYPE_8__ {scalar_t__ ifr_nfl; int /*<<< orphan*/  ifr_id; TYPE_3__* ifr_fl; } ;
struct TYPE_7__ {int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; } ;

/* Variables and functions */
 int BUS_DMASYNC_POSTREAD ; 
 int BUS_DMASYNC_POSTWRITE ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
iflib_rxd_avail(if_ctx_t ctx, iflib_rxq_t rxq, qidx_t cidx, qidx_t budget)
{
	iflib_fl_t fl;
	u_int i;

	for (i = 0, fl = &rxq->ifr_fl[0]; i < rxq->ifr_nfl; i++, fl++)
		bus_dmamap_sync(fl->ifl_ifdi->idi_tag, fl->ifl_ifdi->idi_map,
		    BUS_DMASYNC_POSTREAD | BUS_DMASYNC_POSTWRITE);
	return (ctx->isc_rxd_available(ctx->ifc_softc, rxq->ifr_id, cidx,
	    budget));
}