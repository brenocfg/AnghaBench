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
typedef  int u16 ;
struct rx_ring {int bytes; int itr; int latency; scalar_t__ packets; int /*<<< orphan*/  me; } ;
struct ixl_vsi {int rx_itr_setting; struct i40e_hw* hw; scalar_t__ back; } ;
struct ixl_rx_queue {struct rx_ring rxr; struct ixl_vsi* vsi; } ;
struct ixl_pf {int rx_itr; scalar_t__ dynamic_rx_itr; } ;
struct i40e_hw {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  I40E_PFINT_ITRN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
#define  IXL_AVE_LATENCY 130 
#define  IXL_BULK_LATENCY 129 
 int IXL_ITR_100K ; 
 int IXL_ITR_20K ; 
 int IXL_ITR_8K ; 
 int IXL_ITR_DYNAMIC ; 
#define  IXL_LOW_LATENCY 128 
 int /*<<< orphan*/  IXL_MAX_ITR ; 
 int /*<<< orphan*/  IXL_RX_ITR ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void
ixl_set_queue_rx_itr(struct ixl_rx_queue *que)
{
	struct ixl_vsi	*vsi = que->vsi;
	struct ixl_pf	*pf = (struct ixl_pf *)vsi->back;
	struct i40e_hw	*hw = vsi->hw;
	struct rx_ring	*rxr = &que->rxr;
	u16		rx_itr;
	u16		rx_latency = 0;
	int		rx_bytes;

	/* Idle, do nothing */
	if (rxr->bytes == 0)
		return;

	if (pf->dynamic_rx_itr) {
		rx_bytes = rxr->bytes/rxr->itr;
		rx_itr = rxr->itr;

		/* Adjust latency range */
		switch (rxr->latency) {
		case IXL_LOW_LATENCY:
			if (rx_bytes > 10) {
				rx_latency = IXL_AVE_LATENCY;
				rx_itr = IXL_ITR_20K;
			}
			break;
		case IXL_AVE_LATENCY:
			if (rx_bytes > 20) {
				rx_latency = IXL_BULK_LATENCY;
				rx_itr = IXL_ITR_8K;
			} else if (rx_bytes <= 10) {
				rx_latency = IXL_LOW_LATENCY;
				rx_itr = IXL_ITR_100K;
			}
			break;
		case IXL_BULK_LATENCY:
			if (rx_bytes <= 20) {
				rx_latency = IXL_AVE_LATENCY;
				rx_itr = IXL_ITR_20K;
			}
			break;
       		 }

		rxr->latency = rx_latency;

		if (rx_itr != rxr->itr) {
			/* do an exponential smoothing */
			rx_itr = (10 * rx_itr * rxr->itr) /
			    ((9 * rx_itr) + rxr->itr);
			rxr->itr = min(rx_itr, IXL_MAX_ITR);
			wr32(hw, I40E_PFINT_ITRN(IXL_RX_ITR,
			    rxr->me), rxr->itr);
		}
	} else { /* We may have have toggled to non-dynamic */
		if (vsi->rx_itr_setting & IXL_ITR_DYNAMIC)
			vsi->rx_itr_setting = pf->rx_itr;
		/* Update the hardware if needed */
		if (rxr->itr != vsi->rx_itr_setting) {
			rxr->itr = vsi->rx_itr_setting;
			wr32(hw, I40E_PFINT_ITRN(IXL_RX_ITR,
			    rxr->me), rxr->itr);
		}
	}
	rxr->bytes = 0;
	rxr->packets = 0;
}