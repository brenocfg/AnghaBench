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
struct rx_ring {scalar_t__ bytes; scalar_t__ itr; int /*<<< orphan*/  me; } ;
struct ixl_vsi {scalar_t__ rx_itr_setting; struct i40e_hw* hw; } ;
struct ixl_rx_queue {struct rx_ring rxr; struct ixl_vsi* vsi; } ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFINT_ITRN1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IXL_RX_ITR ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
iavf_set_queue_rx_itr(struct ixl_rx_queue *que)
{
	struct ixl_vsi	*vsi = que->vsi;
	struct i40e_hw	*hw = vsi->hw;
	struct rx_ring	*rxr = &que->rxr;

	/* Idle, do nothing */
	if (rxr->bytes == 0)
		return;

	/* Update the hardware if needed */
	if (rxr->itr != vsi->rx_itr_setting) {
		rxr->itr = vsi->rx_itr_setting;
		wr32(hw, I40E_VFINT_ITRN1(IXL_RX_ITR,
		    que->rxr.me), rxr->itr);
	}
}