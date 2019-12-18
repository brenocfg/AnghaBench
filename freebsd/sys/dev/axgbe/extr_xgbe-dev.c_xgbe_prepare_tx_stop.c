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
struct xgbe_prv_data {int dummy; } ;
struct xgbe_channel {unsigned int queue_index; } ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 unsigned int DMA_DSR0 ; 
 unsigned int DMA_DSR0_TPS_START ; 
 unsigned int DMA_DSR1 ; 
 unsigned int DMA_DSRX_FIRST_QUEUE ; 
 unsigned int DMA_DSRX_INC ; 
 unsigned int DMA_DSRX_QPR ; 
 unsigned int DMA_DSRX_TPS_START ; 
 unsigned int DMA_DSR_Q_WIDTH ; 
 int /*<<< orphan*/  DMA_DSR_TPS_WIDTH ; 
 unsigned int DMA_TPS_STOPPED ; 
 unsigned int DMA_TPS_SUSPENDED ; 
 unsigned int GET_BITS (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 unsigned long XGBE_DMA_STOP_TIMEOUT ; 
 unsigned int XGMAC_IOREAD (struct xgbe_prv_data*,unsigned int) ; 
 unsigned long hz ; 
 unsigned long ticks ; 

__attribute__((used)) static void xgbe_prepare_tx_stop(struct xgbe_prv_data *pdata,
				 struct xgbe_channel *channel)
{
	unsigned int tx_dsr, tx_pos, tx_qidx;
	unsigned int tx_status;
	unsigned long tx_timeout;

	/* Calculate the status register to read and the position within */
	if (channel->queue_index < DMA_DSRX_FIRST_QUEUE) {
		tx_dsr = DMA_DSR0;
		tx_pos = (channel->queue_index * DMA_DSR_Q_WIDTH) +
			 DMA_DSR0_TPS_START;
	} else {
		tx_qidx = channel->queue_index - DMA_DSRX_FIRST_QUEUE;

		tx_dsr = DMA_DSR1 + ((tx_qidx / DMA_DSRX_QPR) * DMA_DSRX_INC);
		tx_pos = ((tx_qidx % DMA_DSRX_QPR) * DMA_DSR_Q_WIDTH) +
			 DMA_DSRX_TPS_START;
	}

	/* The Tx engine cannot be stopped if it is actively processing
	 * descriptors. Wait for the Tx engine to enter the stopped or
	 * suspended state.  Don't wait forever though...
	 */
	tx_timeout = ticks + (XGBE_DMA_STOP_TIMEOUT * hz);
	while (ticks < tx_timeout) {
		tx_status = XGMAC_IOREAD(pdata, tx_dsr);
		tx_status = GET_BITS(tx_status, tx_pos, DMA_DSR_TPS_WIDTH);
		if ((tx_status == DMA_TPS_STOPPED) ||
		    (tx_status == DMA_TPS_SUSPENDED))
			break;

		DELAY(500);
	}
}