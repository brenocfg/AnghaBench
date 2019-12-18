#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  prev; } ;
struct fsldma_chan {TYPE_2__ ld_pending; } ;
struct TYPE_4__ {int /*<<< orphan*/  phys; } ;
struct fsl_desc_sw {int /*<<< orphan*/  tx_list; TYPE_1__ async_tx; int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 scalar_t__ list_empty (TYPE_2__*) ; 
 int /*<<< orphan*/  list_splice_tail_init (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  set_desc_next (struct fsldma_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct fsl_desc_sw* to_fsl_desc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void append_ld_queue(struct fsldma_chan *chan, struct fsl_desc_sw *desc)
{
	struct fsl_desc_sw *tail = to_fsl_desc(chan->ld_pending.prev);

	if (list_empty(&chan->ld_pending))
		goto out_splice;

	/*
	 * Add the hardware descriptor to the chain of hardware descriptors
	 * that already exists in memory.
	 *
	 * This will un-set the EOL bit of the existing transaction, and the
	 * last link in this transaction will become the EOL descriptor.
	 */
	set_desc_next(chan, &tail->hw, desc->async_tx.phys);

	/*
	 * Add the software descriptor and all children to the list
	 * of pending transactions
	 */
out_splice:
	list_splice_tail_init(&desc->tx_list, &chan->ld_pending);
}