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
typedef  int /*<<< orphan*/  u32 ;
struct device {int dummy; } ;
struct caam_jrentry_info {int desc_size; int /*<<< orphan*/  desc_addr_dma; void* cbkarg; void* callbk; int /*<<< orphan*/ * desc_addr_virt; } ;
struct caam_drv_private_jr {int head; int /*<<< orphan*/  inplock; TYPE_1__* rregs; scalar_t__ inpring_avail; int /*<<< orphan*/  inpring; struct caam_jrentry_info* entinfo; int /*<<< orphan*/  tail; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int /*<<< orphan*/  inpring_avail; int /*<<< orphan*/  inpring_jobadd; } ;

/* Variables and functions */
 scalar_t__ CIRC_SPACE (int,int,int) ; 
 int /*<<< orphan*/  DMA_TO_DEVICE ; 
 int EBUSY ; 
 int EIO ; 
 int HDR_JD_LENGTH_MASK ; 
 int JOBR_DEPTH ; 
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 int caam32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_caam_dma (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dma_map_single (struct device*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (struct device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (struct device*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jr_inpentry_set (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ rd_reg32 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg32 (int /*<<< orphan*/ *,int) ; 

int caam_jr_enqueue(struct device *dev, u32 *desc,
		    void (*cbk)(struct device *dev, u32 *desc,
				u32 status, void *areq),
		    void *areq)
{
	struct caam_drv_private_jr *jrp = dev_get_drvdata(dev);
	struct caam_jrentry_info *head_entry;
	int head, tail, desc_size;
	dma_addr_t desc_dma;

	desc_size = (caam32_to_cpu(*desc) & HDR_JD_LENGTH_MASK) * sizeof(u32);
	desc_dma = dma_map_single(dev, desc, desc_size, DMA_TO_DEVICE);
	if (dma_mapping_error(dev, desc_dma)) {
		dev_err(dev, "caam_jr_enqueue(): can't map jobdesc\n");
		return -EIO;
	}

	spin_lock_bh(&jrp->inplock);

	head = jrp->head;
	tail = READ_ONCE(jrp->tail);

	if (!jrp->inpring_avail ||
	    CIRC_SPACE(head, tail, JOBR_DEPTH) <= 0) {
		spin_unlock_bh(&jrp->inplock);
		dma_unmap_single(dev, desc_dma, desc_size, DMA_TO_DEVICE);
		return -EBUSY;
	}

	head_entry = &jrp->entinfo[head];
	head_entry->desc_addr_virt = desc;
	head_entry->desc_size = desc_size;
	head_entry->callbk = (void *)cbk;
	head_entry->cbkarg = areq;
	head_entry->desc_addr_dma = desc_dma;

	jr_inpentry_set(jrp->inpring, head, cpu_to_caam_dma(desc_dma));

	/*
	 * Guarantee that the descriptor's DMA address has been written to
	 * the next slot in the ring before the write index is updated, since
	 * other cores may update this index independently.
	 */
	smp_wmb();

	jrp->head = (head + 1) & (JOBR_DEPTH - 1);

	/*
	 * Ensure that all job information has been written before
	 * notifying CAAM that a new job was added to the input ring
	 * using a memory barrier. The wr_reg32() uses api iowrite32()
	 * to do the register write. iowrite32() issues a memory barrier
	 * before the write operation.
	 */

	wr_reg32(&jrp->rregs->inpring_jobadd, 1);

	jrp->inpring_avail--;
	if (!jrp->inpring_avail)
		jrp->inpring_avail = rd_reg32(&jrp->rregs->inpring_avail);

	spin_unlock_bh(&jrp->inplock);

	return 0;
}