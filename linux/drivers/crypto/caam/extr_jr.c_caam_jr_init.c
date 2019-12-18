#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct caam_drv_private_jr {int inpring_avail; int /*<<< orphan*/  irqtask; int /*<<< orphan*/  irq; int /*<<< orphan*/  ridx; TYPE_1__* rregs; int /*<<< orphan*/  inplock; scalar_t__ tail; scalar_t__ head; scalar_t__ out_ring_read_index; TYPE_2__* entinfo; void* outring; void* inpring; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_4__ {int desc_addr_dma; } ;
struct TYPE_3__ {int /*<<< orphan*/  rconfig_lo; int /*<<< orphan*/  outring_size; int /*<<< orphan*/  inpring_size; int /*<<< orphan*/  outring_base; int /*<<< orphan*/  inpring_base; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 int JOBR_DEPTH ; 
 int JOBR_INTC ; 
 int JOBR_INTC_COUNT_THLD ; 
 int JOBR_INTC_TIME_THLD ; 
 int JRCFG_ICDCT_SHIFT ; 
 int JRCFG_ICTT_SHIFT ; 
 int SIZEOF_JR_INPENTRY ; 
 int SIZEOF_JR_OUTENTRY ; 
 int /*<<< orphan*/  caam_jr_dequeue ; 
 int /*<<< orphan*/  caam_jr_interrupt ; 
 int caam_reset_hw_jr (struct device*) ; 
 int /*<<< orphan*/  clrsetbits_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct caam_drv_private_jr* dev_get_drvdata (struct device*) ; 
 int /*<<< orphan*/  dev_name (struct device*) ; 
 TYPE_2__* devm_kcalloc (struct device*,int,int,int /*<<< orphan*/ ) ; 
 int devm_request_irq (struct device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct device*) ; 
 void* dmam_alloc_coherent (struct device*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  tasklet_kill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wr_reg64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int caam_jr_init(struct device *dev)
{
	struct caam_drv_private_jr *jrp;
	dma_addr_t inpbusaddr, outbusaddr;
	int i, error;

	jrp = dev_get_drvdata(dev);

	error = caam_reset_hw_jr(dev);
	if (error)
		return error;

	jrp->inpring = dmam_alloc_coherent(dev, SIZEOF_JR_INPENTRY *
					   JOBR_DEPTH, &inpbusaddr,
					   GFP_KERNEL);
	if (!jrp->inpring)
		return -ENOMEM;

	jrp->outring = dmam_alloc_coherent(dev, SIZEOF_JR_OUTENTRY *
					   JOBR_DEPTH, &outbusaddr,
					   GFP_KERNEL);
	if (!jrp->outring)
		return -ENOMEM;

	jrp->entinfo = devm_kcalloc(dev, JOBR_DEPTH, sizeof(*jrp->entinfo),
				    GFP_KERNEL);
	if (!jrp->entinfo)
		return -ENOMEM;

	for (i = 0; i < JOBR_DEPTH; i++)
		jrp->entinfo[i].desc_addr_dma = !0;

	/* Setup rings */
	jrp->out_ring_read_index = 0;
	jrp->head = 0;
	jrp->tail = 0;

	wr_reg64(&jrp->rregs->inpring_base, inpbusaddr);
	wr_reg64(&jrp->rregs->outring_base, outbusaddr);
	wr_reg32(&jrp->rregs->inpring_size, JOBR_DEPTH);
	wr_reg32(&jrp->rregs->outring_size, JOBR_DEPTH);

	jrp->inpring_avail = JOBR_DEPTH;

	spin_lock_init(&jrp->inplock);

	/* Select interrupt coalescing parameters */
	clrsetbits_32(&jrp->rregs->rconfig_lo, 0, JOBR_INTC |
		      (JOBR_INTC_COUNT_THLD << JRCFG_ICDCT_SHIFT) |
		      (JOBR_INTC_TIME_THLD << JRCFG_ICTT_SHIFT));

	tasklet_init(&jrp->irqtask, caam_jr_dequeue, (unsigned long)dev);

	/* Connect job ring interrupt handler. */
	error = devm_request_irq(dev, jrp->irq, caam_jr_interrupt, IRQF_SHARED,
				 dev_name(dev), dev);
	if (error) {
		dev_err(dev, "can't connect JobR %d interrupt (%d)\n",
			jrp->ridx, jrp->irq);
		tasklet_kill(&jrp->irqtask);
	}

	return error;
}