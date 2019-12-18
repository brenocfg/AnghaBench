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
struct timb_dma_desc {int /*<<< orphan*/  desc_node; } ;
struct timb_dma_chan {int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; int /*<<< orphan*/  chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  chan2dev (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct timb_dma_desc*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void td_desc_put(struct timb_dma_chan *td_chan,
	struct timb_dma_desc *td_desc)
{
	dev_dbg(chan2dev(&td_chan->chan), "Putting desc: %p\n", td_desc);

	spin_lock_bh(&td_chan->lock);
	list_add(&td_desc->desc_node, &td_chan->free_list);
	spin_unlock_bh(&td_chan->lock);
}