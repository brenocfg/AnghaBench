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
struct TYPE_4__ {int chan_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_1__ chan; } ;
struct st_fdma_chan {TYPE_2__ vchan; TYPE_3__* fdev; scalar_t__ fdesc; } ;
struct dma_chan {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long FDMA_CMD_PAUSE (int) ; 
 int /*<<< orphan*/  FDMA_CMD_SET_OFST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fdma_write (TYPE_3__*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int st_fdma_pause(struct dma_chan *chan)
{
	unsigned long flags;
	struct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	int ch_id = fchan->vchan.chan.chan_id;
	unsigned long cmd = FDMA_CMD_PAUSE(ch_id);

	dev_dbg(fchan->fdev->dev, "pause chan:%d\n", ch_id);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	if (fchan->fdesc)
		fdma_write(fchan->fdev, cmd, FDMA_CMD_SET_OFST);
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	return 0;
}