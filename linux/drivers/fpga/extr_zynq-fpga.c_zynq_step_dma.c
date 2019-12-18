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
typedef  int u32 ;
struct zynq_fpga_priv {scalar_t__ dma_elm; scalar_t__ dma_nelms; int /*<<< orphan*/ * cur_sg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_DEST_LEN_OFFSET ; 
 int /*<<< orphan*/  DMA_DST_ADDR_OFFSET ; 
 int DMA_INVALID_ADDRESS ; 
 int /*<<< orphan*/  DMA_SRC_ADDR_OFFSET ; 
 int DMA_SRC_LAST_TRANSFER ; 
 int /*<<< orphan*/  DMA_SRC_LEN_OFFSET ; 
 int IXR_DMA_DONE_MASK ; 
 int IXR_D_P_DONE_MASK ; 
 int IXR_ERROR_FLAGS_MASK ; 
 int STATUS_DMA_Q_F ; 
 int /*<<< orphan*/  STATUS_OFFSET ; 
 int sg_dma_address (int /*<<< orphan*/ *) ; 
 int sg_dma_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sg_next (int /*<<< orphan*/ *) ; 
 int zynq_fpga_read (struct zynq_fpga_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zynq_fpga_set_irq (struct zynq_fpga_priv*,int) ; 
 int /*<<< orphan*/  zynq_fpga_write (struct zynq_fpga_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void zynq_step_dma(struct zynq_fpga_priv *priv)
{
	u32 addr;
	u32 len;
	bool first;

	first = priv->dma_elm == 0;
	while (priv->cur_sg) {
		/* Feed the DMA queue until it is full. */
		if (zynq_fpga_read(priv, STATUS_OFFSET) & STATUS_DMA_Q_F)
			break;

		addr = sg_dma_address(priv->cur_sg);
		len = sg_dma_len(priv->cur_sg);
		if (priv->dma_elm + 1 == priv->dma_nelms) {
			/* The last transfer waits for the PCAP to finish too,
			 * notice this also changes the irq_mask to ignore
			 * IXR_DMA_DONE_MASK which ensures we do not trigger
			 * the completion too early.
			 */
			addr |= DMA_SRC_LAST_TRANSFER;
			priv->cur_sg = NULL;
		} else {
			priv->cur_sg = sg_next(priv->cur_sg);
			priv->dma_elm++;
		}

		zynq_fpga_write(priv, DMA_SRC_ADDR_OFFSET, addr);
		zynq_fpga_write(priv, DMA_DST_ADDR_OFFSET, DMA_INVALID_ADDRESS);
		zynq_fpga_write(priv, DMA_SRC_LEN_OFFSET, len / 4);
		zynq_fpga_write(priv, DMA_DEST_LEN_OFFSET, 0);
	}

	/* Once the first transfer is queued we can turn on the ISR, future
	 * calls to zynq_step_dma will happen from the ISR context. The
	 * dma_lock spinlock guarentees this handover is done coherently, the
	 * ISR enable is put at the end to avoid another CPU spinning in the
	 * ISR on this lock.
	 */
	if (first && priv->cur_sg) {
		zynq_fpga_set_irq(priv,
				  IXR_DMA_DONE_MASK | IXR_ERROR_FLAGS_MASK);
	} else if (!priv->cur_sg) {
		/* The last transfer changes to DMA & PCAP mode since we do
		 * not want to continue until everything has been flushed into
		 * the PCAP.
		 */
		zynq_fpga_set_irq(priv,
				  IXR_D_P_DONE_MASK | IXR_ERROR_FLAGS_MASK);
	}
}