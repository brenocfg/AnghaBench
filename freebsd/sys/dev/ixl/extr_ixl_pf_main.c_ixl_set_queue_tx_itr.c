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
struct tx_ring {int bytes; int itr; int latency; scalar_t__ packets; int /*<<< orphan*/  me; } ;
struct ixl_vsi {int tx_itr_setting; struct i40e_hw* hw; scalar_t__ back; } ;
struct ixl_tx_queue {struct tx_ring txr; struct ixl_vsi* vsi; } ;
struct ixl_pf {int tx_itr; scalar_t__ dynamic_tx_itr; } ;
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
 int /*<<< orphan*/  IXL_TX_ITR ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wr32 (struct i40e_hw*,int /*<<< orphan*/ ,int) ; 

void
ixl_set_queue_tx_itr(struct ixl_tx_queue *que)
{
	struct ixl_vsi	*vsi = que->vsi;
	struct ixl_pf	*pf = (struct ixl_pf *)vsi->back;
	struct i40e_hw	*hw = vsi->hw;
	struct tx_ring	*txr = &que->txr;
	u16		tx_itr;
	u16		tx_latency = 0;
	int		tx_bytes;


	/* Idle, do nothing */
	if (txr->bytes == 0)
		return;

	if (pf->dynamic_tx_itr) {
		tx_bytes = txr->bytes/txr->itr;
		tx_itr = txr->itr;

		switch (txr->latency) {
		case IXL_LOW_LATENCY:
			if (tx_bytes > 10) {
				tx_latency = IXL_AVE_LATENCY;
				tx_itr = IXL_ITR_20K;
			}
			break;
		case IXL_AVE_LATENCY:
			if (tx_bytes > 20) {
				tx_latency = IXL_BULK_LATENCY;
				tx_itr = IXL_ITR_8K;
			} else if (tx_bytes <= 10) {
				tx_latency = IXL_LOW_LATENCY;
				tx_itr = IXL_ITR_100K;
			}
			break;
		case IXL_BULK_LATENCY:
			if (tx_bytes <= 20) {
				tx_latency = IXL_AVE_LATENCY;
				tx_itr = IXL_ITR_20K;
			}
			break;
		}

		txr->latency = tx_latency;

		if (tx_itr != txr->itr) {
       	         /* do an exponential smoothing */
			tx_itr = (10 * tx_itr * txr->itr) /
			    ((9 * tx_itr) + txr->itr);
			txr->itr = min(tx_itr, IXL_MAX_ITR);
			wr32(hw, I40E_PFINT_ITRN(IXL_TX_ITR,
			    txr->me), txr->itr);
		}

	} else { /* We may have have toggled to non-dynamic */
		if (vsi->tx_itr_setting & IXL_ITR_DYNAMIC)
			vsi->tx_itr_setting = pf->tx_itr;
		/* Update the hardware if needed */
		if (txr->itr != vsi->tx_itr_setting) {
			txr->itr = vsi->tx_itr_setting;
			wr32(hw, I40E_PFINT_ITRN(IXL_TX_ITR,
			    txr->me), txr->itr);
		}
	}
	txr->bytes = 0;
	txr->packets = 0;
	return;
}