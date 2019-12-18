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
struct shdma_ops {int /*<<< orphan*/  (* halt_channel ) (struct shdma_chan*) ;} ;
struct shdma_dev {struct shdma_ops* ops; } ;
struct shdma_chan {scalar_t__ slave_id; int /*<<< orphan*/  desc; int /*<<< orphan*/  chan_lock; scalar_t__ desc_num; int /*<<< orphan*/  ld_free; scalar_t__ real_slave_id; int /*<<< orphan*/  ld_queue; } ;
struct dma_chan {int /*<<< orphan*/ * private; int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  shdma_chan_ld_cleanup (struct shdma_chan*,int) ; 
 int /*<<< orphan*/  shdma_slave_used ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct shdma_chan*) ; 
 struct shdma_chan* to_shdma_chan (struct dma_chan*) ; 
 struct shdma_dev* to_shdma_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shdma_free_chan_resources(struct dma_chan *chan)
{
	struct shdma_chan *schan = to_shdma_chan(chan);
	struct shdma_dev *sdev = to_shdma_dev(chan->device);
	const struct shdma_ops *ops = sdev->ops;
	LIST_HEAD(list);

	/* Protect against ISR */
	spin_lock_irq(&schan->chan_lock);
	ops->halt_channel(schan);
	spin_unlock_irq(&schan->chan_lock);

	/* Now no new interrupts will occur */

	/* Prepared and not submitted descriptors can still be on the queue */
	if (!list_empty(&schan->ld_queue))
		shdma_chan_ld_cleanup(schan, true);

	if (schan->slave_id >= 0) {
		/* The caller is holding dma_list_mutex */
		clear_bit(schan->slave_id, shdma_slave_used);
		chan->private = NULL;
	}

	schan->real_slave_id = 0;

	spin_lock_irq(&schan->chan_lock);

	list_splice_init(&schan->ld_free, &list);
	schan->desc_num = 0;

	spin_unlock_irq(&schan->chan_lock);

	kfree(schan->desc);
}