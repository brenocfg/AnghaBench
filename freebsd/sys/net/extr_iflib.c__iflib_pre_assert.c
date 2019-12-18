#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* if_softc_ctx_t ;
struct TYPE_5__ {TYPE_1__* isc_txrx; } ;
struct TYPE_4__ {int /*<<< orphan*/  ift_rxd_flush; int /*<<< orphan*/  ift_rxd_refill; int /*<<< orphan*/  ift_rxd_pkt_get; int /*<<< orphan*/  ift_rxd_available; int /*<<< orphan*/  ift_txd_credits_update; int /*<<< orphan*/  ift_txd_flush; int /*<<< orphan*/  ift_txd_encap; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
_iflib_pre_assert(if_softc_ctx_t scctx)
{

	MPASS(scctx->isc_txrx->ift_txd_encap);
	MPASS(scctx->isc_txrx->ift_txd_flush);
	MPASS(scctx->isc_txrx->ift_txd_credits_update);
	MPASS(scctx->isc_txrx->ift_rxd_available);
	MPASS(scctx->isc_txrx->ift_rxd_pkt_get);
	MPASS(scctx->isc_txrx->ift_rxd_refill);
	MPASS(scctx->isc_txrx->ift_rxd_flush);
}