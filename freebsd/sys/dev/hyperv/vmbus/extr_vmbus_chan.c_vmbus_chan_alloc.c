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
struct vmbus_softc {int /*<<< orphan*/  vmbus_dev; } ;
struct vmbus_channel {int ch_refs; int /*<<< orphan*/  ch_poll_timeo; int /*<<< orphan*/  ch_poll_task; int /*<<< orphan*/  ch_txbr; int /*<<< orphan*/  ch_rxbr; int /*<<< orphan*/  ch_subchans; int /*<<< orphan*/  ch_orphan_lock; int /*<<< orphan*/  ch_subchan_lock; struct vmbus_softc* ch_vmbus; int /*<<< orphan*/ * ch_monprm; int /*<<< orphan*/  ch_monprm_dma; } ;
struct hyperv_mon_param {int dummy; } ;

/* Variables and functions */
 int BUS_DMA_WAITOK ; 
 int BUS_DMA_ZERO ; 
 int /*<<< orphan*/  HYPERCALL_PARAM_ALIGN ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vmbus_channel*) ; 
 int /*<<< orphan*/  bus_get_dma_tag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * hyperv_dmamem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int) ; 
 struct vmbus_channel* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_init (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vmbus_chan_poll_task ; 
 int /*<<< orphan*/  vmbus_rxbr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_txbr_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct vmbus_channel *
vmbus_chan_alloc(struct vmbus_softc *sc)
{
	struct vmbus_channel *chan;

	chan = malloc(sizeof(*chan), M_DEVBUF, M_WAITOK | M_ZERO);

	chan->ch_monprm = hyperv_dmamem_alloc(bus_get_dma_tag(sc->vmbus_dev),
	    HYPERCALL_PARAM_ALIGN, 0, sizeof(struct hyperv_mon_param),
	    &chan->ch_monprm_dma, BUS_DMA_WAITOK | BUS_DMA_ZERO);
	if (chan->ch_monprm == NULL) {
		device_printf(sc->vmbus_dev, "monprm alloc failed\n");
		free(chan, M_DEVBUF);
		return NULL;
	}

	chan->ch_refs = 1;
	chan->ch_vmbus = sc;
	mtx_init(&chan->ch_subchan_lock, "vmbus subchan", NULL, MTX_DEF);
	sx_init(&chan->ch_orphan_lock, "vmbus chorphan");
	TAILQ_INIT(&chan->ch_subchans);
	vmbus_rxbr_init(&chan->ch_rxbr);
	vmbus_txbr_init(&chan->ch_txbr);

	TASK_INIT(&chan->ch_poll_task, 0, vmbus_chan_poll_task, chan);
	callout_init(&chan->ch_poll_timeo, 1);

	return chan;
}