#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ qidx_t ;
typedef  TYPE_2__* iflib_txq_t ;
typedef  TYPE_3__* if_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  ifc_softc; int /*<<< orphan*/  (* isc_txd_flush ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ;} ;
struct TYPE_8__ {scalar_t__ ift_db_pending; scalar_t__ ift_npending; scalar_t__ ift_pidx; int /*<<< orphan*/  ift_id; TYPE_1__* ift_ifdi; } ;
struct TYPE_7__ {int /*<<< orphan*/  idi_map; int /*<<< orphan*/  idi_tag; } ;

/* Variables and functions */
 int BUS_DMASYNC_PREREAD ; 
 int BUS_DMASYNC_PREWRITE ; 
 scalar_t__ TXQ_MAX_DB_DEFERRED (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline bool
iflib_txd_db_check(if_ctx_t ctx, iflib_txq_t txq, int ring, qidx_t in_use)
{
	qidx_t dbval, max;
	bool rang;

	rang = false;
	max = TXQ_MAX_DB_DEFERRED(txq, in_use);
	if (ring || txq->ift_db_pending >= max) {
		dbval = txq->ift_npending ? txq->ift_npending : txq->ift_pidx;
		bus_dmamap_sync(txq->ift_ifdi->idi_tag, txq->ift_ifdi->idi_map,
		    BUS_DMASYNC_PREREAD | BUS_DMASYNC_PREWRITE);
		ctx->isc_txd_flush(ctx->ifc_softc, txq->ift_id, dbval);
		txq->ift_db_pending = txq->ift_npending = 0;
		rang = true;
	}
	return (rang);
}