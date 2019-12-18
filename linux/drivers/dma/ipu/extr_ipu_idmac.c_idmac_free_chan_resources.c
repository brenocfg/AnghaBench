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
struct idmac_channel {scalar_t__ status; int /*<<< orphan*/  chan_mutex; int /*<<< orphan*/  eof_irq; } ;
struct idmac {int dummy; } ;
struct dma_chan {int chan_id; int /*<<< orphan*/  device; } ;
struct TYPE_2__ {int /*<<< orphan*/  tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int IDMAC_IC_7 ; 
 scalar_t__ IPU_CHANNEL_FREE ; 
 int /*<<< orphan*/  __idmac_terminate_all (struct dma_chan*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct idmac_channel*) ; 
 int /*<<< orphan*/  ic_eof ; 
 int /*<<< orphan*/  ic_sof ; 
 int /*<<< orphan*/  ipu_irq_unmap (int) ; 
 int /*<<< orphan*/  ipu_uninit_channel (struct idmac*,struct idmac_channel*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 struct idmac* to_idmac (int /*<<< orphan*/ ) ; 
 struct idmac_channel* to_idmac_chan (struct dma_chan*) ; 
 TYPE_1__* to_ipu (struct idmac*) ; 

__attribute__((used)) static void idmac_free_chan_resources(struct dma_chan *chan)
{
	struct idmac_channel *ichan = to_idmac_chan(chan);
	struct idmac *idmac = to_idmac(chan->device);

	mutex_lock(&ichan->chan_mutex);

	__idmac_terminate_all(chan);

	if (ichan->status > IPU_CHANNEL_FREE) {
#ifdef DEBUG
		if (chan->chan_id == IDMAC_IC_7) {
			if (ic_sof > 0) {
				free_irq(ic_sof, ichan);
				ipu_irq_unmap(69);
				ic_sof = -EINVAL;
			}
			if (ic_eof > 0) {
				free_irq(ic_eof, ichan);
				ipu_irq_unmap(70);
				ic_eof = -EINVAL;
			}
		}
#endif
		free_irq(ichan->eof_irq, ichan);
		ipu_irq_unmap(chan->chan_id);
	}

	ichan->status = IPU_CHANNEL_FREE;

	ipu_uninit_channel(idmac, ichan);

	mutex_unlock(&ichan->chan_mutex);

	tasklet_schedule(&to_ipu(idmac)->tasklet);
}