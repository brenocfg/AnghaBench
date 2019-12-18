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
typedef  int uint32_t ;
struct vmbus_softc {int dummy; } ;
struct vmbus_msghc {int dummy; } ;
struct vmbus_channel {int ch_stflags; scalar_t__ ch_bufring_gpadl; int /*<<< orphan*/ * ch_bufring; int /*<<< orphan*/  ch_bufring_dma; int /*<<< orphan*/  ch_id; int /*<<< orphan*/ * ch_tq; int /*<<< orphan*/  ch_task; int /*<<< orphan*/  ch_sysctl_ctx; struct vmbus_softc* ch_vmbus; } ;
struct TYPE_2__ {int /*<<< orphan*/  chm_type; } ;
struct vmbus_chanmsg_chclose {int /*<<< orphan*/  chm_chanid; TYPE_1__ chm_hdr; } ;

/* Variables and functions */
 int EISCONN ; 
 int ENXIO ; 
 int /*<<< orphan*/  VMBUS_CHANMSG_TYPE_CHCLOSE ; 
 int VMBUS_CHAN_ST_OPENED ; 
 scalar_t__ atomic_cmpset_int (int*,int,int) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  hyperv_dmamem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_chan_clear_chmap (struct vmbus_channel*) ; 
 int vmbus_chan_gpadl_disconnect (struct vmbus_channel*,scalar_t__) ; 
 int /*<<< orphan*/  vmbus_chan_poll_cancel (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_printf (struct vmbus_channel*,char*,int /*<<< orphan*/ ,...) ; 
 struct vmbus_chanmsg_chclose* vmbus_msghc_dataptr (struct vmbus_msghc*) ; 
 int vmbus_msghc_exec_noresult (struct vmbus_msghc*) ; 
 struct vmbus_msghc* vmbus_msghc_get (struct vmbus_softc*,int) ; 
 int /*<<< orphan*/  vmbus_msghc_put (struct vmbus_softc*,struct vmbus_msghc*) ; 

__attribute__((used)) static int
vmbus_chan_close_internal(struct vmbus_channel *chan)
{
	struct vmbus_softc *sc = chan->ch_vmbus;
	struct vmbus_msghc *mh;
	struct vmbus_chanmsg_chclose *req;
	uint32_t old_stflags;
	int error;

	/*
	 * NOTE:
	 * Sub-channels are closed upon their primary channel closing,
	 * so they can be closed even before they are opened.
	 */
	for (;;) {
		old_stflags = chan->ch_stflags;
		if (atomic_cmpset_int(&chan->ch_stflags, old_stflags,
		    old_stflags & ~VMBUS_CHAN_ST_OPENED))
			break;
	}
	if ((old_stflags & VMBUS_CHAN_ST_OPENED) == 0) {
		/* Not opened yet; done */
		if (bootverbose) {
			vmbus_chan_printf(chan, "chan%u not opened\n",
			    chan->ch_id);
		}
		return (0);
	}

	/*
	 * Free this channel's sysctl tree attached to its device's
	 * sysctl tree.
	 */
	sysctl_ctx_free(&chan->ch_sysctl_ctx);

	/*
	 * Cancel polling, if it is enabled.
	 */
	vmbus_chan_poll_cancel(chan);

	/*
	 * NOTE:
	 * Order is critical.  This channel _must_ be uninstalled first,
	 * else the channel task may be enqueued by the IDT after it has
	 * been drained.
	 */
	vmbus_chan_clear_chmap(chan);
	taskqueue_drain(chan->ch_tq, &chan->ch_task);
	chan->ch_tq = NULL;

	/*
	 * Close this channel.
	 */
	mh = vmbus_msghc_get(sc, sizeof(*req));
	if (mh == NULL) {
		vmbus_chan_printf(chan,
		    "can not get msg hypercall for chclose(chan%u)\n",
		    chan->ch_id);
		error = ENXIO;
		goto disconnect;
	}

	req = vmbus_msghc_dataptr(mh);
	req->chm_hdr.chm_type = VMBUS_CHANMSG_TYPE_CHCLOSE;
	req->chm_chanid = chan->ch_id;

	error = vmbus_msghc_exec_noresult(mh);
	vmbus_msghc_put(sc, mh);

	if (error) {
		vmbus_chan_printf(chan,
		    "chclose(chan%u) msg hypercall exec failed: %d\n",
		    chan->ch_id, error);
		goto disconnect;
	}

	if (bootverbose)
		vmbus_chan_printf(chan, "chan%u closed\n", chan->ch_id);

disconnect:
	/*
	 * Disconnect the TX+RX bufrings from this channel.
	 */
	if (chan->ch_bufring_gpadl != 0) {
		int error1;

		error1 = vmbus_chan_gpadl_disconnect(chan,
		    chan->ch_bufring_gpadl);
		if (error1) {
			/*
			 * XXX
			 * The bufring GPADL is still connected; abandon
			 * this bufring, instead of having mysterious
			 * crash or trashed data later on.
			 */
			vmbus_chan_printf(chan, "chan%u bufring GPADL "
			    "is still connected after close\n", chan->ch_id);
			chan->ch_bufring = NULL;
			/*
			 * Give caller a hint that the bufring GPADL is
			 * still connected.
			 */
			error = EISCONN;
		}
		chan->ch_bufring_gpadl = 0;
	}

	/*
	 * Destroy the TX+RX bufrings.
	 */
	if (chan->ch_bufring != NULL) {
		hyperv_dmamem_free(&chan->ch_bufring_dma, chan->ch_bufring);
		chan->ch_bufring = NULL;
	}
	return (error);
}