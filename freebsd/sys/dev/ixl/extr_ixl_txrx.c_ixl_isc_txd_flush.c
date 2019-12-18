#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct tx_ring {int /*<<< orphan*/  tail; } ;
struct ixl_vsi {int /*<<< orphan*/  hw; TYPE_2__* shared; TYPE_1__* tx_queues; } ;
typedef  scalar_t__ qidx_t ;
struct TYPE_4__ {scalar_t__* isc_ntxd; } ;
struct TYPE_3__ {struct tx_ring txr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPASS (int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ixl_isc_txd_flush(void *arg, uint16_t txqid, qidx_t pidx)
{
	struct ixl_vsi *vsi = arg;
	struct tx_ring *txr = &vsi->tx_queues[txqid].txr;

 	/*
	 * Advance the Transmit Descriptor Tail (Tdt), this tells the
	 * hardware that this frame is available to transmit.
 	 */
	/* Check for ENDLESS_TX MDD event */
	MPASS(pidx < vsi->shared->isc_ntxd[0]);
	wr32(vsi->hw, txr->tail, pidx);
}