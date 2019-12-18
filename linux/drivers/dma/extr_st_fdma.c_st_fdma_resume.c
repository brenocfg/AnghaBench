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
struct st_fdma_chan {TYPE_2__ vchan; scalar_t__ fdesc; TYPE_3__* fdev; } ;
struct dma_chan {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned long FDMA_CH_CMD_DATA_MASK ; 
 int /*<<< orphan*/  FDMA_CH_CMD_OFST ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 unsigned long fchan_read (struct st_fdma_chan*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fchan_write (struct st_fdma_chan*,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct st_fdma_chan* to_st_fdma_chan (struct dma_chan*) ; 

__attribute__((used)) static int st_fdma_resume(struct dma_chan *chan)
{
	unsigned long flags;
	unsigned long val;
	struct st_fdma_chan *fchan = to_st_fdma_chan(chan);
	int ch_id = fchan->vchan.chan.chan_id;

	dev_dbg(fchan->fdev->dev, "resume chan:%d\n", ch_id);

	spin_lock_irqsave(&fchan->vchan.lock, flags);
	if (fchan->fdesc) {
		val = fchan_read(fchan, FDMA_CH_CMD_OFST);
		val &= FDMA_CH_CMD_DATA_MASK;
		fchan_write(fchan, val, FDMA_CH_CMD_OFST);
	}
	spin_unlock_irqrestore(&fchan->vchan.lock, flags);

	return 0;
}