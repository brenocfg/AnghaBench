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
typedef  int /*<<< orphan*/  u32 ;
struct ioatdma_device {struct ioatdma_chan** idx; } ;
struct ioatdma_chan {scalar_t__ reg_base; int /*<<< orphan*/  prep_lock; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 scalar_t__ IOAT_CHANERR_OFFSET ; 
 int /*<<< orphan*/  IOAT_CHAN_DOWN ; 
 int IOAT_MAX_CHANS ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readl (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void ioat_resume(struct ioatdma_device *ioat_dma)
{
	struct ioatdma_chan *ioat_chan;
	u32 chanerr;
	int i;

	for (i = 0; i < IOAT_MAX_CHANS; i++) {
		ioat_chan = ioat_dma->idx[i];
		if (!ioat_chan)
			continue;

		spin_lock_bh(&ioat_chan->prep_lock);
		clear_bit(IOAT_CHAN_DOWN, &ioat_chan->state);
		spin_unlock_bh(&ioat_chan->prep_lock);

		chanerr = readl(ioat_chan->reg_base + IOAT_CHANERR_OFFSET);
		writel(chanerr, ioat_chan->reg_base + IOAT_CHANERR_OFFSET);

		/* no need to reset as shutdown already did that */
	}
}