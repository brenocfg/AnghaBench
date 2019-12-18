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
struct pl08x_driver_data {TYPE_2__* adev; TYPE_1__* pd; } ;
struct TYPE_6__ {int /*<<< orphan*/  desc_free; } ;
struct pl08x_dma_chan {int signal; char* bus_id; TYPE_3__ vc; int /*<<< orphan*/  name; struct pl08x_dma_chan* cd; int /*<<< orphan*/  periph_buses; int /*<<< orphan*/  state; struct pl08x_driver_data* host; } ;
struct dma_device {int /*<<< orphan*/  channels; } ;
struct TYPE_5__ {int /*<<< orphan*/  dev; } ;
struct TYPE_4__ {int /*<<< orphan*/  mem_buses; struct pl08x_dma_chan* slave_channels; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PL08X_CHAN_IDLE ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*,int,char*) ; 
 int /*<<< orphan*/  kasprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  kfree (struct pl08x_dma_chan*) ; 
 void* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pl08x_desc_free ; 
 int /*<<< orphan*/  pl08x_dma_slave_init (struct pl08x_dma_chan*) ; 
 int /*<<< orphan*/  vchan_init (TYPE_3__*,struct dma_device*) ; 

__attribute__((used)) static int pl08x_dma_init_virtual_channels(struct pl08x_driver_data *pl08x,
		struct dma_device *dmadev, unsigned int channels, bool slave)
{
	struct pl08x_dma_chan *chan;
	int i;

	INIT_LIST_HEAD(&dmadev->channels);

	/*
	 * Register as many many memcpy as we have physical channels,
	 * we won't always be able to use all but the code will have
	 * to cope with that situation.
	 */
	for (i = 0; i < channels; i++) {
		chan = kzalloc(sizeof(*chan), GFP_KERNEL);
		if (!chan)
			return -ENOMEM;

		chan->host = pl08x;
		chan->state = PL08X_CHAN_IDLE;
		chan->signal = -1;

		if (slave) {
			chan->cd = &pl08x->pd->slave_channels[i];
			/*
			 * Some implementations have muxed signals, whereas some
			 * use a mux in front of the signals and need dynamic
			 * assignment of signals.
			 */
			chan->signal = i;
			pl08x_dma_slave_init(chan);
		} else {
			chan->cd = kzalloc(sizeof(*chan->cd), GFP_KERNEL);
			if (!chan->cd) {
				kfree(chan);
				return -ENOMEM;
			}
			chan->cd->bus_id = "memcpy";
			chan->cd->periph_buses = pl08x->pd->mem_buses;
			chan->name = kasprintf(GFP_KERNEL, "memcpy%d", i);
			if (!chan->name) {
				kfree(chan->cd);
				kfree(chan);
				return -ENOMEM;
			}
		}
		dev_dbg(&pl08x->adev->dev,
			 "initialize virtual channel \"%s\"\n",
			 chan->name);

		chan->vc.desc_free = pl08x_desc_free;
		vchan_init(&chan->vc, dmadev);
	}
	dev_info(&pl08x->adev->dev, "initialized %d virtual %s channels\n",
		 i, slave ? "slave" : "memcpy");
	return i;
}