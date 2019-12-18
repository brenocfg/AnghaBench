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
struct s5p_aes_dev {int busy; int /*<<< orphan*/  hash_tasklet; int /*<<< orphan*/  lock; int /*<<< orphan*/  hash_sg_iter; struct ablkcipher_request* req; int /*<<< orphan*/  sg_src; int /*<<< orphan*/  sg_dst; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  hash_flags; } ;
struct platform_device {int dummy; } ;
struct ablkcipher_request {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  FCINTPEND ; 
 int /*<<< orphan*/  FCINTSTAT ; 
 int /*<<< orphan*/  HASH_FLAGS_OUTPUT_READY ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int SSS_FCINTSTAT_BRDMAINT ; 
 int SSS_FCINTSTAT_BTDMAINT ; 
 int SSS_FCINTSTAT_HDONEINT ; 
 int SSS_FCINTSTAT_HPARTINT ; 
 int SSS_FCINTSTAT_HRDMAINT ; 
 int SSS_HASH_PAUSE ; 
 int SSS_HASH_STATUS_MSG_DONE ; 
 int SSS_HASH_STATUS_PARTIAL_DONE ; 
 int SSS_READ (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSS_REG_HASH_CTRL_PAUSE ; 
 int /*<<< orphan*/  SSS_REG_HASH_STATUS ; 
 int /*<<< orphan*/  SSS_WRITE (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 
 struct s5p_aes_dev* platform_get_drvdata (struct platform_device*) ; 
 int /*<<< orphan*/  s5p_aes_complete (struct ablkcipher_request*,int) ; 
 int s5p_aes_rx (struct s5p_aes_dev*) ; 
 int s5p_aes_tx (struct s5p_aes_dev*) ; 
 int s5p_hash_rx (struct s5p_aes_dev*) ; 
 int /*<<< orphan*/  s5p_hash_write (struct s5p_aes_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  s5p_set_dma_hashdata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_set_dma_indata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_set_dma_outdata (struct s5p_aes_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  s5p_sg_done (struct s5p_aes_dev*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ sg_is_last (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t s5p_aes_interrupt(int irq, void *dev_id)
{
	struct platform_device *pdev = dev_id;
	struct s5p_aes_dev *dev = platform_get_drvdata(pdev);
	struct ablkcipher_request *req;
	int err_dma_tx = 0;
	int err_dma_rx = 0;
	int err_dma_hx = 0;
	bool tx_end = false;
	bool hx_end = false;
	unsigned long flags;
	u32 status, st_bits;
	int err;

	spin_lock_irqsave(&dev->lock, flags);

	/*
	 * Handle rx or tx interrupt. If there is still data (scatterlist did not
	 * reach end), then map next scatterlist entry.
	 * In case of such mapping error, s5p_aes_complete() should be called.
	 *
	 * If there is no more data in tx scatter list, call s5p_aes_complete()
	 * and schedule new tasklet.
	 *
	 * Handle hx interrupt. If there is still data map next entry.
	 */
	status = SSS_READ(dev, FCINTSTAT);
	if (status & SSS_FCINTSTAT_BRDMAINT)
		err_dma_rx = s5p_aes_rx(dev);

	if (status & SSS_FCINTSTAT_BTDMAINT) {
		if (sg_is_last(dev->sg_dst))
			tx_end = true;
		err_dma_tx = s5p_aes_tx(dev);
	}

	if (status & SSS_FCINTSTAT_HRDMAINT)
		err_dma_hx = s5p_hash_rx(dev);

	st_bits = status & (SSS_FCINTSTAT_BRDMAINT | SSS_FCINTSTAT_BTDMAINT |
				SSS_FCINTSTAT_HRDMAINT);
	/* clear DMA bits */
	SSS_WRITE(dev, FCINTPEND, st_bits);

	/* clear HASH irq bits */
	if (status & (SSS_FCINTSTAT_HDONEINT | SSS_FCINTSTAT_HPARTINT)) {
		/* cannot have both HPART and HDONE */
		if (status & SSS_FCINTSTAT_HPARTINT)
			st_bits = SSS_HASH_STATUS_PARTIAL_DONE;

		if (status & SSS_FCINTSTAT_HDONEINT)
			st_bits = SSS_HASH_STATUS_MSG_DONE;

		set_bit(HASH_FLAGS_OUTPUT_READY, &dev->hash_flags);
		s5p_hash_write(dev, SSS_REG_HASH_STATUS, st_bits);
		hx_end = true;
		/* when DONE or PART, do not handle HASH DMA */
		err_dma_hx = 0;
	}

	if (err_dma_rx < 0) {
		err = err_dma_rx;
		goto error;
	}
	if (err_dma_tx < 0) {
		err = err_dma_tx;
		goto error;
	}

	if (tx_end) {
		s5p_sg_done(dev);
		if (err_dma_hx == 1)
			s5p_set_dma_hashdata(dev, dev->hash_sg_iter);

		spin_unlock_irqrestore(&dev->lock, flags);

		s5p_aes_complete(dev->req, 0);
		/* Device is still busy */
		tasklet_schedule(&dev->tasklet);
	} else {
		/*
		 * Writing length of DMA block (either receiving or
		 * transmitting) will start the operation immediately, so this
		 * should be done at the end (even after clearing pending
		 * interrupts to not miss the interrupt).
		 */
		if (err_dma_tx == 1)
			s5p_set_dma_outdata(dev, dev->sg_dst);
		if (err_dma_rx == 1)
			s5p_set_dma_indata(dev, dev->sg_src);
		if (err_dma_hx == 1)
			s5p_set_dma_hashdata(dev, dev->hash_sg_iter);

		spin_unlock_irqrestore(&dev->lock, flags);
	}

	goto hash_irq_end;

error:
	s5p_sg_done(dev);
	dev->busy = false;
	req = dev->req;
	if (err_dma_hx == 1)
		s5p_set_dma_hashdata(dev, dev->hash_sg_iter);

	spin_unlock_irqrestore(&dev->lock, flags);
	s5p_aes_complete(req, err);

hash_irq_end:
	/*
	 * Note about else if:
	 *   when hash_sg_iter reaches end and its UPDATE op,
	 *   issue SSS_HASH_PAUSE and wait for HPART irq
	 */
	if (hx_end)
		tasklet_schedule(&dev->hash_tasklet);
	else if (err_dma_hx == 2)
		s5p_hash_write(dev, SSS_REG_HASH_CTRL_PAUSE,
			       SSS_HASH_PAUSE);

	return IRQ_HANDLED;
}