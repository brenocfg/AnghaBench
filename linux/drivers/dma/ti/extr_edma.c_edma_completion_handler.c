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
struct edma_desc {scalar_t__ processed; scalar_t__ pset_nr; scalar_t__ processed_stat; scalar_t__ residue; scalar_t__ residue_stat; scalar_t__ sg_len; int /*<<< orphan*/  vdesc; scalar_t__ cyclic; } ;
struct TYPE_5__ {TYPE_1__* device; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_2__ chan; } ;
struct edma_chan {TYPE_3__ vchan; int /*<<< orphan*/  ch_num; struct edma_desc* edesc; } ;
struct device {int dummy; } ;
struct TYPE_4__ {struct device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  edma_execute (struct edma_chan*) ; 
 int /*<<< orphan*/  edma_pause (struct edma_chan*) ; 
 int /*<<< orphan*/  edma_stop (struct edma_chan*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cookie_complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_cyclic_callback (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void edma_completion_handler(struct edma_chan *echan)
{
	struct device *dev = echan->vchan.chan.device->dev;
	struct edma_desc *edesc;

	spin_lock(&echan->vchan.lock);
	edesc = echan->edesc;
	if (edesc) {
		if (edesc->cyclic) {
			vchan_cyclic_callback(&edesc->vdesc);
			spin_unlock(&echan->vchan.lock);
			return;
		} else if (edesc->processed == edesc->pset_nr) {
			edesc->residue = 0;
			edma_stop(echan);
			vchan_cookie_complete(&edesc->vdesc);
			echan->edesc = NULL;

			dev_dbg(dev, "Transfer completed on channel %d\n",
				echan->ch_num);
		} else {
			dev_dbg(dev, "Sub transfer completed on channel %d\n",
				echan->ch_num);

			edma_pause(echan);

			/* Update statistics for tx_status */
			edesc->residue -= edesc->sg_len;
			edesc->residue_stat = edesc->residue;
			edesc->processed_stat = edesc->processed;
		}
		edma_execute(echan);
	}

	spin_unlock(&echan->vchan.lock);
}