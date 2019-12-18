#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct tx_ring {int tx_cidx_processed; } ;
struct ixl_vsi {struct ixl_tx_queue* tx_queues; TYPE_1__* shared; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {scalar_t__* isc_ntxd; } ;

/* Variables and functions */
 int ixl_get_tx_head (struct ixl_tx_queue*) ; 

__attribute__((used)) static int
ixl_isc_txd_credits_update_hwb(void *arg, uint16_t qid, bool clear)
{
	struct ixl_vsi          *vsi = arg;
	if_softc_ctx_t          scctx = vsi->shared;
	struct ixl_tx_queue     *que = &vsi->tx_queues[qid];
	struct tx_ring		*txr = &que->txr;
	int			 head, credits;

	/* Get the Head WB value */
	head = ixl_get_tx_head(que);

	credits = head - txr->tx_cidx_processed;
	if (credits < 0)
		credits += scctx->isc_ntxd[0];
	if (clear)
		txr->tx_cidx_processed = head;

	return (credits);
}