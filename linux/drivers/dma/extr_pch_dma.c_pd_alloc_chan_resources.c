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
struct pch_dma_desc {int /*<<< orphan*/  desc_node; } ;
struct pch_dma_chan {int descs_allocated; int /*<<< orphan*/  lock; int /*<<< orphan*/  free_list; } ;
struct dma_chan {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan2dev (struct dma_chan*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dma_cookie_init (struct dma_chan*) ; 
 int init_nr_desc_per_channel ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_splice (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct pch_dma_desc* pdc_alloc_desc (struct dma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pdc_enable_irq (struct dma_chan*,int) ; 
 int /*<<< orphan*/  pdc_is_idle (struct pch_dma_chan*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tmp_list ; 
 struct pch_dma_chan* to_pd_chan (struct dma_chan*) ; 

__attribute__((used)) static int pd_alloc_chan_resources(struct dma_chan *chan)
{
	struct pch_dma_chan *pd_chan = to_pd_chan(chan);
	struct pch_dma_desc *desc;
	LIST_HEAD(tmp_list);
	int i;

	if (!pdc_is_idle(pd_chan)) {
		dev_dbg(chan2dev(chan), "DMA channel not idle ?\n");
		return -EIO;
	}

	if (!list_empty(&pd_chan->free_list))
		return pd_chan->descs_allocated;

	for (i = 0; i < init_nr_desc_per_channel; i++) {
		desc = pdc_alloc_desc(chan, GFP_KERNEL);

		if (!desc) {
			dev_warn(chan2dev(chan),
				"Only allocated %d initial descriptors\n", i);
			break;
		}

		list_add_tail(&desc->desc_node, &tmp_list);
	}

	spin_lock_irq(&pd_chan->lock);
	list_splice(&tmp_list, &pd_chan->free_list);
	pd_chan->descs_allocated = i;
	dma_cookie_init(chan);
	spin_unlock_irq(&pd_chan->lock);

	pdc_enable_irq(chan, 1);

	return pd_chan->descs_allocated;
}