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
typedef  int /*<<< orphan*/  vmbus_chan_callback_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  task_fn_t ;
struct vmbus_softc {int dummy; } ;
struct vmbus_msghc {int dummy; } ;
struct vmbus_message {scalar_t__ msg_data; } ;
struct vmbus_channel {int ch_flags; scalar_t__ ch_bufring_gpadl; int /*<<< orphan*/  ch_stflags; int /*<<< orphan*/  ch_sysctl_ctx; int /*<<< orphan*/  ch_id; int /*<<< orphan*/  ch_vcpuid; int /*<<< orphan*/  ch_rxbr; int /*<<< orphan*/  ch_txbr; int /*<<< orphan*/  ch_task; int /*<<< orphan*/  ch_cpuid; struct vmbus_softc* ch_vmbus; int /*<<< orphan*/  ch_tq; void* ch_cbarg; int /*<<< orphan*/  ch_cb; } ;
struct vmbus_chanmsg_chopen_resp {int chm_status; } ;
struct TYPE_2__ {int /*<<< orphan*/  chm_type; } ;
struct vmbus_chanmsg_chopen {scalar_t__ chm_gpadl; int chm_txbr_pgcnt; int /*<<< orphan*/  chm_udata; int /*<<< orphan*/  chm_vcpuid; int /*<<< orphan*/  chm_openid; int /*<<< orphan*/  chm_chanid; TYPE_1__ chm_hdr; } ;
struct vmbus_chan_br {int cbr_txsz; int cbr_rxsz; int cbr_paddr; int /*<<< orphan*/ * cbr; } ;

/* Variables and functions */
 int EINVAL ; 
 int EISCONN ; 
 int ENXIO ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PAGE_MASK ; 
 int PAGE_SHIFT ; 
 int REVOKE_LINGER ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct vmbus_channel*) ; 
 int VMBUS_CHANMSG_CHOPEN_UDATA_SIZE ; 
 int /*<<< orphan*/  VMBUS_CHANMSG_TYPE_CHOPEN ; 
 int VMBUS_CHAN_FLAG_BATCHREAD ; 
 int /*<<< orphan*/  VMBUS_CHAN_ST_OPENED ; 
 int /*<<< orphan*/  VMBUS_CHAN_ST_OPENED_SHIFT ; 
 int /*<<< orphan*/  VMBUS_PCPU_GET (struct vmbus_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_clear_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ atomic_testandset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bootverbose ; 
 int /*<<< orphan*/  event_tq ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,void const*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int /*<<< orphan*/  sysctl_ctx_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmbus_chan_clear_chmap (struct vmbus_channel*) ; 
 int vmbus_chan_gpadl_connect (struct vmbus_channel*,int,int,scalar_t__*) ; 
 int vmbus_chan_gpadl_disconnect (struct vmbus_channel*,scalar_t__) ; 
 scalar_t__ vmbus_chan_is_revoked (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_printf (struct vmbus_channel*,char*,int,...) ; 
 int /*<<< orphan*/  vmbus_chan_set_chmap (struct vmbus_channel*) ; 
 int /*<<< orphan*/  vmbus_chan_sysctl_create (struct vmbus_channel*) ; 
 int /*<<< orphan*/ * vmbus_chan_task ; 
 int /*<<< orphan*/ * vmbus_chan_task_nobatch ; 
 int /*<<< orphan*/  vmbus_chan_update_evtflagcnt (struct vmbus_softc*,struct vmbus_channel*) ; 
 struct vmbus_chanmsg_chopen* vmbus_msghc_dataptr (struct vmbus_msghc*) ; 
 int vmbus_msghc_exec (struct vmbus_softc*,struct vmbus_msghc*) ; 
 int /*<<< orphan*/  vmbus_msghc_exec_cancel (struct vmbus_softc*,struct vmbus_msghc*) ; 
 struct vmbus_msghc* vmbus_msghc_get (struct vmbus_softc*,int) ; 
 struct vmbus_message* vmbus_msghc_poll_result (struct vmbus_softc*,struct vmbus_msghc*) ; 
 int /*<<< orphan*/  vmbus_msghc_put (struct vmbus_softc*,struct vmbus_msghc*) ; 
 int /*<<< orphan*/  vmbus_rxbr_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vmbus_txbr_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

int
vmbus_chan_open_br(struct vmbus_channel *chan, const struct vmbus_chan_br *cbr,
    const void *udata, int udlen, vmbus_chan_callback_t cb, void *cbarg)
{
	struct vmbus_softc *sc = chan->ch_vmbus;
	const struct vmbus_message *msg;
	struct vmbus_chanmsg_chopen *req;
	struct vmbus_msghc *mh;
	uint32_t status;
	int error, txbr_size, rxbr_size;
	task_fn_t *task_fn;
	uint8_t *br;

	if (udlen > VMBUS_CHANMSG_CHOPEN_UDATA_SIZE) {
		vmbus_chan_printf(chan,
		    "invalid udata len %d for chan%u\n", udlen, chan->ch_id);
		return (EINVAL);
	}

	br = cbr->cbr;
	txbr_size = cbr->cbr_txsz;
	rxbr_size = cbr->cbr_rxsz;
	KASSERT((txbr_size & PAGE_MASK) == 0,
	    ("send bufring size is not multiple page"));
	KASSERT((rxbr_size & PAGE_MASK) == 0,
	    ("recv bufring size is not multiple page"));
	KASSERT((cbr->cbr_paddr & PAGE_MASK) == 0,
	    ("bufring is not page aligned"));

	/*
	 * Zero out the TX/RX bufrings, in case that they were used before.
	 */
	memset(br, 0, txbr_size + rxbr_size);

	if (atomic_testandset_int(&chan->ch_stflags,
	    VMBUS_CHAN_ST_OPENED_SHIFT))
		panic("double-open chan%u", chan->ch_id);

	chan->ch_cb = cb;
	chan->ch_cbarg = cbarg;

	vmbus_chan_update_evtflagcnt(sc, chan);

	chan->ch_tq = VMBUS_PCPU_GET(chan->ch_vmbus, event_tq, chan->ch_cpuid);
	if (chan->ch_flags & VMBUS_CHAN_FLAG_BATCHREAD)
		task_fn = vmbus_chan_task;
	else
		task_fn = vmbus_chan_task_nobatch;
	TASK_INIT(&chan->ch_task, 0, task_fn, chan);

	/* TX bufring comes first */
	vmbus_txbr_setup(&chan->ch_txbr, br, txbr_size);
	/* RX bufring immediately follows TX bufring */
	vmbus_rxbr_setup(&chan->ch_rxbr, br + txbr_size, rxbr_size);

	/* Create sysctl tree for this channel */
	vmbus_chan_sysctl_create(chan);

	/*
	 * Connect the bufrings, both RX and TX, to this channel.
	 */
	error = vmbus_chan_gpadl_connect(chan, cbr->cbr_paddr,
	    txbr_size + rxbr_size, &chan->ch_bufring_gpadl);
	if (error) {
		vmbus_chan_printf(chan,
		    "failed to connect bufring GPADL to chan%u\n", chan->ch_id);
		goto failed;
	}

	/*
	 * Install this channel, before it is opened, but after everything
	 * else has been setup.
	 */
	vmbus_chan_set_chmap(chan);

	/*
	 * Open channel w/ the bufring GPADL on the target CPU.
	 */
	mh = vmbus_msghc_get(sc, sizeof(*req));
	if (mh == NULL) {
		vmbus_chan_printf(chan,
		    "can not get msg hypercall for chopen(chan%u)\n",
		    chan->ch_id);
		error = ENXIO;
		goto failed;
	}

	req = vmbus_msghc_dataptr(mh);
	req->chm_hdr.chm_type = VMBUS_CHANMSG_TYPE_CHOPEN;
	req->chm_chanid = chan->ch_id;
	req->chm_openid = chan->ch_id;
	req->chm_gpadl = chan->ch_bufring_gpadl;
	req->chm_vcpuid = chan->ch_vcpuid;
	req->chm_txbr_pgcnt = txbr_size >> PAGE_SHIFT;
	if (udlen > 0)
		memcpy(req->chm_udata, udata, udlen);

	error = vmbus_msghc_exec(sc, mh);
	if (error) {
		vmbus_chan_printf(chan,
		    "chopen(chan%u) msg hypercall exec failed: %d\n",
		    chan->ch_id, error);
		vmbus_msghc_put(sc, mh);
		goto failed;
	}

	for (;;) {
		msg = vmbus_msghc_poll_result(sc, mh);
		if (msg != NULL)
			break;
		if (vmbus_chan_is_revoked(chan)) {
			int i;

			/*
			 * NOTE:
			 * Hypervisor does _not_ send response CHOPEN to
			 * a revoked channel.
			 */
			vmbus_chan_printf(chan,
			    "chan%u is revoked, when it is being opened\n",
			    chan->ch_id);

			/*
			 * XXX
			 * Add extra delay before cancel the hypercall
			 * execution; mainly to close any possible
			 * CHRESCIND and CHOPEN_RESP races on the
			 * hypervisor side.
			 */
#define REVOKE_LINGER	100
			for (i = 0; i < REVOKE_LINGER; ++i) {
				msg = vmbus_msghc_poll_result(sc, mh);
				if (msg != NULL)
					break;
				pause("rchopen", 1);
			}
#undef REVOKE_LINGER
			if (msg == NULL)
				vmbus_msghc_exec_cancel(sc, mh);
			break;
		}
		pause("chopen", 1);
	}
	if (msg != NULL) {
		status = ((const struct vmbus_chanmsg_chopen_resp *)
		    msg->msg_data)->chm_status;
	} else {
		/* XXX any non-0 value is ok here. */
		status = 0xff;
	}

	vmbus_msghc_put(sc, mh);

	if (status == 0) {
		if (bootverbose)
			vmbus_chan_printf(chan, "chan%u opened\n", chan->ch_id);
		return (0);
	}

	vmbus_chan_printf(chan, "failed to open chan%u\n", chan->ch_id);
	error = ENXIO;

failed:
	sysctl_ctx_free(&chan->ch_sysctl_ctx);
	vmbus_chan_clear_chmap(chan);
	if (chan->ch_bufring_gpadl != 0) {
		int error1;

		error1 = vmbus_chan_gpadl_disconnect(chan,
		    chan->ch_bufring_gpadl);
		if (error1) {
			/*
			 * Give caller a hint that the bufring GPADL is still
			 * connected.
			 */
			error = EISCONN;
		}
		chan->ch_bufring_gpadl = 0;
	}
	atomic_clear_int(&chan->ch_stflags, VMBUS_CHAN_ST_OPENED);
	return (error);
}