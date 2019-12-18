#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ error; } ;
typedef  TYPE_1__ xdma_transfer_status_t ;
typedef  int /*<<< orphan*/  xdma_channel_t ;
struct xdma_request {int block_num; } ;
struct pdma_softc {int dummy; } ;
struct pdma_channel {int flags; int cur_desc; int /*<<< orphan*/ * xchan; int /*<<< orphan*/  index; struct xdma_request* req; } ;

/* Variables and functions */
 int CHAN_DESCR_RELINK ; 
 int /*<<< orphan*/  PDMA_DCS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PDMA_DIRQP ; 
 int PDMA_NCHANNELS ; 
 int READ4 (struct pdma_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WRITE4 (struct pdma_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  chan_start (struct pdma_softc*,struct pdma_channel*) ; 
 struct pdma_channel* pdma_channels ; 
 int /*<<< orphan*/  xdma_callback (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
pdma_intr(void *arg)
{
	struct xdma_request *req;
	xdma_transfer_status_t status;
	struct pdma_channel *chan;
	struct pdma_softc *sc;
	xdma_channel_t *xchan;
	int pending;
	int i;

	sc = arg;

	pending = READ4(sc, PDMA_DIRQP);

	/* Ack all the channels. */
	WRITE4(sc, PDMA_DIRQP, 0);

	for (i = 0; i < PDMA_NCHANNELS; i++) {
		if (pending & (1 << i)) {
			chan = &pdma_channels[i];
			xchan = chan->xchan;
			req = chan->req;

			/* TODO: check for AR, HLT error bits here. */

			/* Disable channel */
			WRITE4(sc, PDMA_DCS(chan->index), 0);

			if (chan->flags & CHAN_DESCR_RELINK) {
				/* Enable again */
				chan->cur_desc = (chan->cur_desc + 1) % \
				    req->block_num;
				chan_start(sc, chan);
			}

			status.error = 0;
			xdma_callback(chan->xchan, &status);
		}
	}
}