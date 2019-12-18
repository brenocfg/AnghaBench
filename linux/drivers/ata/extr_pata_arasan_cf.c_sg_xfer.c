#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct scatterlist {int dummy; } ;
struct arasan_cf_dev {int pbase; TYPE_3__* host; scalar_t__ vbase; TYPE_2__* qc; } ;
typedef  int dma_addr_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int flags; } ;
struct TYPE_5__ {TYPE_1__ tf; } ;

/* Variables and functions */
 int ATA_TFLAG_WRITE ; 
 int EXT_READ_PORT ; 
 int EXT_WRITE_PORT ; 
 int /*<<< orphan*/  FIFO_SIZE ; 
 int /*<<< orphan*/  MAX_XFER_COUNT ; 
 int XFER_COUNT_MASK ; 
 scalar_t__ XFER_CTR ; 
 int XFER_START ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int dma_xfer (struct arasan_cf_dev*,int,int,int) ; 
 int min (int,int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 int sg_dma_address (struct scatterlist*) ; 
 int sg_dma_len (struct scatterlist*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int wait4buf (struct arasan_cf_dev*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int sg_xfer(struct arasan_cf_dev *acdev, struct scatterlist *sg)
{
	dma_addr_t dest = 0, src = 0;
	u32 xfer_cnt, sglen, dma_len, xfer_ctr;
	u32 write = acdev->qc->tf.flags & ATA_TFLAG_WRITE;
	unsigned long flags;
	int ret = 0;

	sglen = sg_dma_len(sg);
	if (write) {
		src = sg_dma_address(sg);
		dest = acdev->pbase + EXT_WRITE_PORT;
	} else {
		dest = sg_dma_address(sg);
		src = acdev->pbase + EXT_READ_PORT;
	}

	/*
	 * For each sg:
	 * MAX_XFER_COUNT data will be transferred before we get transfer
	 * complete interrupt. Between after FIFO_SIZE data
	 * buffer available interrupt will be generated. At this time we will
	 * fill FIFO again: max FIFO_SIZE data.
	 */
	while (sglen) {
		xfer_cnt = min(sglen, MAX_XFER_COUNT);
		spin_lock_irqsave(&acdev->host->lock, flags);
		xfer_ctr = readl(acdev->vbase + XFER_CTR) &
			~XFER_COUNT_MASK;
		writel(xfer_ctr | xfer_cnt | XFER_START,
				acdev->vbase + XFER_CTR);
		spin_unlock_irqrestore(&acdev->host->lock, flags);

		/* continue dma xfers until current sg is completed */
		while (xfer_cnt) {
			/* wait for read to complete */
			if (!write) {
				ret = wait4buf(acdev);
				if (ret)
					goto fail;
			}

			/* read/write FIFO in chunk of FIFO_SIZE */
			dma_len = min(xfer_cnt, FIFO_SIZE);
			ret = dma_xfer(acdev, src, dest, dma_len);
			if (ret) {
				dev_err(acdev->host->dev, "dma failed");
				goto fail;
			}

			if (write)
				src += dma_len;
			else
				dest += dma_len;

			sglen -= dma_len;
			xfer_cnt -= dma_len;

			/* wait for write to complete */
			if (write) {
				ret = wait4buf(acdev);
				if (ret)
					goto fail;
			}
		}
	}

fail:
	spin_lock_irqsave(&acdev->host->lock, flags);
	writel(readl(acdev->vbase + XFER_CTR) & ~XFER_START,
			acdev->vbase + XFER_CTR);
	spin_unlock_irqrestore(&acdev->host->lock, flags);

	return ret;
}