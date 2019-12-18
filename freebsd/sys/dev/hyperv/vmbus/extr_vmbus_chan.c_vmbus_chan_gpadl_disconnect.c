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
typedef  scalar_t__ uint32_t ;
struct vmbus_softc {int dummy; } ;
struct vmbus_msghc {int dummy; } ;
struct vmbus_channel {int /*<<< orphan*/  ch_id; struct vmbus_softc* ch_vmbus; } ;
struct TYPE_2__ {int /*<<< orphan*/  chm_type; } ;
struct vmbus_chanmsg_gpadl_disconn {scalar_t__ chm_gpadl; int /*<<< orphan*/  chm_chanid; TYPE_1__ chm_hdr; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VMBUS_CHANMSG_TYPE_GPADL_DISCONN ; 
 int /*<<< orphan*/  vmbus_chan_printf (struct vmbus_channel*,char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ vmbus_chan_wait_revoke (struct vmbus_channel*,int) ; 
 struct vmbus_chanmsg_gpadl_disconn* vmbus_msghc_dataptr (struct vmbus_msghc*) ; 
 int vmbus_msghc_exec (struct vmbus_softc*,struct vmbus_msghc*) ; 
 struct vmbus_msghc* vmbus_msghc_get (struct vmbus_softc*,int) ; 
 int /*<<< orphan*/  vmbus_msghc_put (struct vmbus_softc*,struct vmbus_msghc*) ; 
 int /*<<< orphan*/  vmbus_msghc_wait_result (struct vmbus_softc*,struct vmbus_msghc*) ; 

int
vmbus_chan_gpadl_disconnect(struct vmbus_channel *chan, uint32_t gpadl)
{
	struct vmbus_softc *sc = chan->ch_vmbus;
	struct vmbus_msghc *mh;
	struct vmbus_chanmsg_gpadl_disconn *req;
	int error;

	KASSERT(gpadl != 0, ("GPADL is zero"));

	mh = vmbus_msghc_get(sc, sizeof(*req));
	if (mh == NULL) {
		vmbus_chan_printf(chan,
		    "can not get msg hypercall for gpadl_disconn(chan%u)\n",
		    chan->ch_id);
		return (EBUSY);
	}

	req = vmbus_msghc_dataptr(mh);
	req->chm_hdr.chm_type = VMBUS_CHANMSG_TYPE_GPADL_DISCONN;
	req->chm_chanid = chan->ch_id;
	req->chm_gpadl = gpadl;

	error = vmbus_msghc_exec(sc, mh);
	if (error) {
		vmbus_msghc_put(sc, mh);

		if (vmbus_chan_wait_revoke(chan, true)) {
			/*
			 * Error is benign; this channel is revoked,
			 * so this GPADL will not be touched anymore.
			 */
			vmbus_chan_printf(chan,
			    "gpadl_disconn(revoked chan%u) msg hypercall "
			    "exec failed: %d\n", chan->ch_id, error);
			return (0);
		}
		vmbus_chan_printf(chan,
		    "gpadl_disconn(chan%u) msg hypercall exec failed: %d\n",
		    chan->ch_id, error);
		return (error);
	}

	vmbus_msghc_wait_result(sc, mh);
	/* Discard result; no useful information */
	vmbus_msghc_put(sc, mh);

	return (0);
}