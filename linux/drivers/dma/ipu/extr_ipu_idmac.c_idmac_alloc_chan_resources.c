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
struct idmac_channel {scalar_t__ status; int eof_irq; char* eof_name; } ;
struct idmac {int dummy; } ;
struct dma_chan {int client_count; int chan_id; TYPE_1__* dev; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  device; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ IDMAC_IC_7 ; 
 scalar_t__ IPU_CHANNEL_FREE ; 
 scalar_t__ IPU_CHANNEL_INITIALIZED ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,scalar_t__,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dma_cookie_init (struct dma_chan*) ; 
 int ic_eof ; 
 int /*<<< orphan*/  ic_eof_irq ; 
 int ic_sof ; 
 int /*<<< orphan*/  ic_sof_irq ; 
 int /*<<< orphan*/  idmac_interrupt ; 
 int /*<<< orphan*/  ipu_disable_channel (struct idmac*,struct idmac_channel*,int) ; 
 int ipu_init_channel (struct idmac*,struct idmac_channel*) ; 
 void* ipu_irq_map (int) ; 
 int /*<<< orphan*/  ipu_irq_unmap (scalar_t__) ; 
 int /*<<< orphan*/  ipu_uninit_channel (struct idmac*,struct idmac_channel*) ; 
 int request_irq (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,struct idmac_channel*) ; 
 struct idmac* to_idmac (int /*<<< orphan*/ ) ; 
 struct idmac_channel* to_idmac_chan (struct dma_chan*) ; 

__attribute__((used)) static int idmac_alloc_chan_resources(struct dma_chan *chan)
{
	struct idmac_channel *ichan = to_idmac_chan(chan);
	struct idmac *idmac = to_idmac(chan->device);
	int ret;

	/* dmaengine.c now guarantees to only offer free channels */
	BUG_ON(chan->client_count > 1);
	WARN_ON(ichan->status != IPU_CHANNEL_FREE);

	dma_cookie_init(chan);

	ret = ipu_irq_map(chan->chan_id);
	if (ret < 0)
		goto eimap;

	ichan->eof_irq = ret;

	/*
	 * Important to first disable the channel, because maybe someone
	 * used it before us, e.g., the bootloader
	 */
	ipu_disable_channel(idmac, ichan, true);

	ret = ipu_init_channel(idmac, ichan);
	if (ret < 0)
		goto eichan;

	ret = request_irq(ichan->eof_irq, idmac_interrupt, 0,
			  ichan->eof_name, ichan);
	if (ret < 0)
		goto erirq;

#ifdef DEBUG
	if (chan->chan_id == IDMAC_IC_7) {
		ic_sof = ipu_irq_map(69);
		if (ic_sof > 0) {
			ret = request_irq(ic_sof, ic_sof_irq, 0, "IC SOF", ichan);
			if (ret)
				dev_err(&chan->dev->device, "request irq failed for IC SOF");
		}
		ic_eof = ipu_irq_map(70);
		if (ic_eof > 0) {
			ret = request_irq(ic_eof, ic_eof_irq, 0, "IC EOF", ichan);
			if (ret)
				dev_err(&chan->dev->device, "request irq failed for IC EOF");
		}
	}
#endif

	ichan->status = IPU_CHANNEL_INITIALIZED;

	dev_dbg(&chan->dev->device, "Found channel 0x%x, irq %d\n",
		chan->chan_id, ichan->eof_irq);

	return ret;

erirq:
	ipu_uninit_channel(idmac, ichan);
eichan:
	ipu_irq_unmap(chan->chan_id);
eimap:
	return ret;
}