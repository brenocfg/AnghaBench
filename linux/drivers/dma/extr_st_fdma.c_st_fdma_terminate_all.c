#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int chan_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  lock; TYPE_1__ chan; } ;
struct st_fdma_chan {TYPE_2__ vchan; int /*<<< orphan*/ * fdesc; TYPE_4__* fdev; } ;
struct dma_chan {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long FDMA_CMD_PAUSE (int) ; 
 int /*<<< orphan*/  FDMA_CMD_SET_OFST ; 
 int /*<<< orphan*/  LIST_HEAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fdma_write (TYPE_4__*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  head ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 
 int /*<<< orphan*/  vchan_dma_desc_free_list (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vchan_get_all_descriptors (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int st_fdma_terminate_all(struct dma_chan *chan)
{
	unsigned long flags;
	LIST_HEAD(head);
	struct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	int ch_id = fchan->vchan.chan.chan_id;
	unsigned long cmd = FDMA_CMD_PAUSE(ch_id);

	dev_dbg(fchan->fdev->dev, "terminate chan:%d\n", ch_id);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	fdma_write(fchan->fdev, cmd, FDMA_CMD_SET_OFST);
	fchan->fdesc = NULL;
	vchan_get_all_descriptors(&fchan->vchan, &head);
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);
	vchan_dma_desc_free_list(&fchan->vchan, &head);

	return 0;
}