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
struct edma_chan {int* slot; int alloced; int hw_triggered; int /*<<< orphan*/  ch_num; int /*<<< orphan*/ * tc; TYPE_1__* ecc; int /*<<< orphan*/  vchan; } ;
struct dma_chan {int /*<<< orphan*/  chan_id; } ;
struct device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dummy_slot; struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDMA_CHAN_SLOT (int /*<<< orphan*/ ) ; 
 int EDMA_MAX_SLOTS ; 
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_free_channel (struct edma_chan*) ; 
 int /*<<< orphan*/  edma_free_slot (TYPE_1__*,int) ; 
 int /*<<< orphan*/  edma_set_chmap (struct edma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_stop (struct edma_chan*) ; 
 struct edma_chan* to_edma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_free_chan_resources (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edma_free_chan_resources(struct dma_chan *chan)
{
	struct edma_chan *echan = to_edma_chan(chan);
	struct device *dev = echan->ecc->dev;
	int i;

	/* Terminate transfers */
	edma_stop(echan);

	vchan_free_chan_resources(&echan->vchan);

	/* Free EDMA PaRAM slots */
	for (i = 0; i < EDMA_MAX_SLOTS; i++) {
		if (echan->slot[i] >= 0) {
			edma_free_slot(echan->ecc, echan->slot[i]);
			echan->slot[i] = -1;
		}
	}

	/* Set entry slot to the dummy slot */
	edma_set_chmap(echan, echan->ecc->dummy_slot);

	/* Free EDMA channel */
	if (echan->alloced) {
		edma_free_channel(echan);
		echan->alloced = false;
	}

	echan->tc = NULL;
	echan->hw_triggered = false;

	dev_dbg(dev, "Free eDMA channel %d for virt channel %d\n",
		EDMA_CHAN_SLOT(echan->ch_num), chan->chan_id);
}