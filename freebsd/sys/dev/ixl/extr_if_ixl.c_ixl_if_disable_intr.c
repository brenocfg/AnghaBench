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
struct ixl_vsi {int num_rx_queues; TYPE_1__* shared; struct ixl_rx_queue* rx_queues; struct i40e_hw* hw; } ;
struct ixl_rx_queue {scalar_t__ msix; } ;
struct ixl_pf {struct ixl_vsi vsi; } ;
struct i40e_hw {int dummy; } ;
typedef  int /*<<< orphan*/  if_ctx_t ;
struct TYPE_2__ {scalar_t__ isc_intr; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_LNKLST0 ; 
 scalar_t__ IFLIB_INTR_MSIX ; 
 struct ixl_pf* iflib_get_softc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ixl_disable_queue (struct i40e_hw*,scalar_t__) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ixl_if_disable_intr(if_ctx_t ctx)
{
	struct ixl_pf *pf = iflib_get_softc(ctx);
	struct ixl_vsi *vsi = &pf->vsi;
	struct i40e_hw		*hw = vsi->hw;
	struct ixl_rx_queue	*rx_que = vsi->rx_queues;

	if (vsi->shared->isc_intr == IFLIB_INTR_MSIX) {
		for (int i = 0; i < vsi->num_rx_queues; i++, rx_que++)
			ixl_disable_queue(hw, rx_que->msix - 1);
	} else {
		// Set PFINT_LNKLST0 FIRSTQ_INDX to 0x7FF
		// stops queues from triggering interrupts
		wr32(hw, I40E_PFINT_LNKLST0, 0x7FF);
	}
}