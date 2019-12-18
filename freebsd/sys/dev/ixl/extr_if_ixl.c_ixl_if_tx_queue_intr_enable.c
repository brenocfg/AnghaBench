#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  size_t uint16_t ;
struct ixl_vsi {struct ixl_tx_queue* tx_queues; struct i40e_hw* hw; } ;
struct ixl_tx_queue {scalar_t__ msix; } ;
struct ixl_pf {struct ixl_vsi vsi; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;

/* Variables and functions */
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_enable_queue (struct i40e_hw*,scalar_t__) ; 

__attribute__((used)) static int
ixl_if_tx_queue_intr_enable(if_ctx_t ctx, uint16_t txqid)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct i40e_hw *hw = vsi->hw;
	struct ixl_tx_queue *tx_que = &vsi->tx_queues[txqid];

	ixl_enable_queue(hw, tx_que->msix - 1);
	return (0);
}