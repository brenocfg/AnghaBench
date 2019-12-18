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
struct rx_ring {int /*<<< orphan*/  latency; int /*<<< orphan*/  itr; } ;
struct ixl_vsi {int num_rx_queues; int /*<<< orphan*/  rx_itr_setting; struct ixl_rx_queue* rx_queues; } ;
struct ixl_rx_queue {struct rx_ring rxr; } ;
struct i40e_hw {int dummy; } ;
struct iavf_sc {int /*<<< orphan*/  rx_itr; struct ixl_vsi vsi; struct i40e_hw hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_VFINT_ITRN1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IXL_AVE_LATENCY ; 
 int /*<<< orphan*/  IXL_RX_ITR ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
iavf_configure_rx_itr(struct iavf_sc *sc)
{
	struct i40e_hw		*hw = &sc->hw;
	struct ixl_vsi		*vsi = &sc->vsi;
	struct ixl_rx_queue	*que = vsi->rx_queues;

	vsi->rx_itr_setting = sc->rx_itr;

	for (int i = 0; i < vsi->num_rx_queues; i++, que++) {
		struct rx_ring 	*rxr = &que->rxr;

		wr32(hw, I40E_VFINT_ITRN1(IXL_RX_ITR, i),
		    vsi->rx_itr_setting);
		rxr->itr = vsi->rx_itr_setting;
		rxr->latency = IXL_AVE_LATENCY;
	}
}