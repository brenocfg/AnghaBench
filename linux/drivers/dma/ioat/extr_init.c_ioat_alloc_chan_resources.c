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
typedef  int u64 ;
typedef  int u32 ;
struct ioatdma_chan {int alloc_order; scalar_t__ reg_base; TYPE_1__* ioat_dma; int /*<<< orphan*/  cleanup_lock; int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  state; scalar_t__ tail; scalar_t__ issued; scalar_t__ head; struct ioat_ring_ent** ring; scalar_t__ completion_dma; int /*<<< orphan*/  completion; } ;
struct ioat_ring_ent {int dummy; } ;
struct dma_chan {int dummy; } ;
struct TYPE_2__ {scalar_t__ version; int /*<<< orphan*/  completion_pool; } ;

/* Variables and functions */
 int EFAULT ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOWAIT ; 
 scalar_t__ IOAT_CHANCMP_OFFSET_HIGH ; 
 scalar_t__ IOAT_CHANCMP_OFFSET_LOW ; 
 scalar_t__ IOAT_CHANCTRL_OFFSET ; 
 int /*<<< orphan*/  IOAT_CHANCTRL_RUN ; 
 scalar_t__ IOAT_CHANERR_OFFSET ; 
 scalar_t__ IOAT_CHAN_LTR_ACTIVE_OFFSET ; 
 int IOAT_CHAN_LTR_ACTIVE_SNLATSCALE ; 
 int IOAT_CHAN_LTR_ACTIVE_SNREQMNT ; 
 int IOAT_CHAN_LTR_ACTIVE_SNVAL ; 
 scalar_t__ IOAT_CHAN_LTR_IDLE_OFFSET ; 
 int IOAT_CHAN_LTR_IDLE_SNLATSCALE ; 
 int IOAT_CHAN_LTR_IDLE_SNREQMNT ; 
 int IOAT_CHAN_LTR_IDLE_SNVAL ; 
 int /*<<< orphan*/  IOAT_CHAN_LTR_SWSEL_ACTIVE ; 
 scalar_t__ IOAT_CHAN_LTR_SWSEL_OFFSET ; 
 int IOAT_MAX_ORDER ; 
 int /*<<< orphan*/  IOAT_RUN ; 
 scalar_t__ IOAT_VER_3_4 ; 
 int /*<<< orphan*/  dev_WARN (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_pool_zalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 struct ioat_ring_ent** ioat_alloc_ring (struct dma_chan*,int,int /*<<< orphan*/ ) ; 
 int ioat_chansts (struct ioatdma_chan*) ; 
 int /*<<< orphan*/  ioat_free_chan_resources (struct dma_chan*) ; 
 int /*<<< orphan*/  ioat_start_null_desc (struct ioatdma_chan*) ; 
 scalar_t__ is_ioat_active (int) ; 
 scalar_t__ is_ioat_idle (int) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_dev (struct ioatdma_chan*) ; 
 struct ioatdma_chan* to_ioat_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int ioat_alloc_chan_resources(struct dma_chan *c)
{
	struct ioatdma_chan *ioat_chan = to_ioat_chan(c);
	struct ioat_ring_ent **ring;
	u64 status;
	int order;
	int i = 0;
	u32 chanerr;

	/* have we already been set up? */
	if (ioat_chan->ring)
		return 1 << ioat_chan->alloc_order;

	/* Setup register to interrupt and write completion status on error */
	writew(IOAT_CHANCTRL_RUN, ioat_chan->reg_base + IOAT_CHANCTRL_OFFSET);

	/* allocate a completion writeback area */
	/* doing 2 32bit writes to mmio since 1 64b write doesn't work */
	ioat_chan->completion =
		dma_pool_zalloc(ioat_chan->ioat_dma->completion_pool,
				GFP_NOWAIT, &ioat_chan->completion_dma);
	if (!ioat_chan->completion)
		return -ENOMEM;

	writel(((u64)ioat_chan->completion_dma) & 0x00000000FFFFFFFF,
	       ioat_chan->reg_base + IOAT_CHANCMP_OFFSET_LOW);
	writel(((u64)ioat_chan->completion_dma) >> 32,
	       ioat_chan->reg_base + IOAT_CHANCMP_OFFSET_HIGH);

	order = IOAT_MAX_ORDER;
	ring = ioat_alloc_ring(c, order, GFP_NOWAIT);
	if (!ring)
		return -ENOMEM;

	spin_lock_bh(&ioat_chan->cleanup_lock);
	spin_lock_bh(&ioat_chan->prep_lock);
	ioat_chan->ring = ring;
	ioat_chan->head = 0;
	ioat_chan->issued = 0;
	ioat_chan->tail = 0;
	ioat_chan->alloc_order = order;
	set_bit(IOAT_RUN, &ioat_chan->state);
	spin_unlock_bh(&ioat_chan->prep_lock);
	spin_unlock_bh(&ioat_chan->cleanup_lock);

	/* Setting up LTR values for 3.4 or later */
	if (ioat_chan->ioat_dma->version >= IOAT_VER_3_4) {
		u32 lat_val;

		lat_val = IOAT_CHAN_LTR_ACTIVE_SNVAL |
			IOAT_CHAN_LTR_ACTIVE_SNLATSCALE |
			IOAT_CHAN_LTR_ACTIVE_SNREQMNT;
		writel(lat_val, ioat_chan->reg_base +
				IOAT_CHAN_LTR_ACTIVE_OFFSET);

		lat_val = IOAT_CHAN_LTR_IDLE_SNVAL |
			  IOAT_CHAN_LTR_IDLE_SNLATSCALE |
			  IOAT_CHAN_LTR_IDLE_SNREQMNT;
		writel(lat_val, ioat_chan->reg_base +
				IOAT_CHAN_LTR_IDLE_OFFSET);

		/* Select to active */
		writeb(IOAT_CHAN_LTR_SWSEL_ACTIVE,
		       ioat_chan->reg_base +
		       IOAT_CHAN_LTR_SWSEL_OFFSET);
	}

	ioat_start_null_desc(ioat_chan);

	/* check that we got off the ground */
	do {
		udelay(1);
		status = ioat_chansts(ioat_chan);
	} while (i++ < 20 && !is_ioat_active(status) && !is_ioat_idle(status));

	if (is_ioat_active(status) || is_ioat_idle(status))
		return 1 << ioat_chan->alloc_order;

	chanerr = readl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);

	dev_WARN(to_dev(ioat_chan),
		 "failed to start channel chanerr: %#x\n", chanerr);
	ioat_free_chan_resources(c);
	return -EFAULT;
}