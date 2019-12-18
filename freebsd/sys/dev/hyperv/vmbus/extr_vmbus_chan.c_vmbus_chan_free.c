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
struct vmbus_channel {scalar_t__ ch_subchan_cnt; int ch_stflags; scalar_t__ ch_refs; scalar_t__ ch_poll_intvl; int /*<<< orphan*/  ch_txbr; int /*<<< orphan*/  ch_rxbr; int /*<<< orphan*/  ch_orphan_lock; int /*<<< orphan*/  ch_subchan_lock; int /*<<< orphan*/  ch_monprm; int /*<<< orphan*/  ch_monprm_dma; int /*<<< orphan*/  ch_id; int /*<<< orphan*/ * ch_orphan_xact; int /*<<< orphan*/  ch_subchans; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 scalar_t__ TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int VMBUS_CHAN_ST_ONLIST ; 
 int VMBUS_CHAN_ST_ONPRIL ; 
 int VMBUS_CHAN_ST_ONSUBL ; 
 int VMBUS_CHAN_ST_OPENED ; 
 int /*<<< orphan*/  free (struct vmbus_channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hyperv_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_rxbr_deinit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_txbr_deinit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vmbus_chan_free(struct vmbus_channel *chan)
{

	KASSERT(TAILQ_EMPTY(&chan->ch_subchans) && chan->ch_subchan_cnt == 0,
	    ("still owns sub-channels"));
	KASSERT((chan->ch_stflags &
	    (VMBUS_CHAN_ST_OPENED |
	     VMBUS_CHAN_ST_ONPRIL |
	     VMBUS_CHAN_ST_ONSUBL |
	     VMBUS_CHAN_ST_ONLIST)) == 0, ("free busy channel"));
	KASSERT(chan->ch_orphan_xact == NULL,
	    ("still has orphan xact installed"));
	KASSERT(chan->ch_refs == 0, ("chan%u: invalid refcnt %d",
	    chan->ch_id, chan->ch_refs));
	KASSERT(chan->ch_poll_intvl == 0, ("chan%u: polling is activated",
	    chan->ch_id));

	hyperv_dmamem_free(&chan->ch_monprm_dma, chan->ch_monprm);
	mtx_destroy(&chan->ch_subchan_lock);
	sx_destroy(&chan->ch_orphan_lock);
	vmbus_rxbr_deinit(&chan->ch_rxbr);
	vmbus_txbr_deinit(&chan->ch_txbr);
	free(chan, M_DEVBUF);
}