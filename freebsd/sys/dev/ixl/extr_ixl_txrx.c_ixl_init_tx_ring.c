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
struct tx_ring {int /*<<< orphan*/  tail; scalar_t__ tx_base; } ;
struct ixl_vsi {int /*<<< orphan*/  hw; scalar_t__ enable_head_writeback; TYPE_1__* shared; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
struct i40e_tx_desc {int dummy; } ;
struct TYPE_2__ {int* isc_ntxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (void*,int) ; 
 int /*<<< orphan*/  wr32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
ixl_init_tx_ring(struct ixl_vsi *vsi, struct ixl_tx_queue *que)
{
	struct tx_ring *txr = &que->txr;

	/* Clear the old ring contents */
	bzero((void *)txr->tx_base,
	      (sizeof(struct i40e_tx_desc)) *
	      (vsi->shared->isc_ntxd[0] + (vsi->enable_head_writeback ? 1 : 0)));

	wr32(vsi->hw, txr->tail, 0);
}