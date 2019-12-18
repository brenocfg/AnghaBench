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
struct TYPE_2__ {int size; scalar_t__ waiting; } ;
struct drbd_request {unsigned int rq_state; int /*<<< orphan*/  kref; TYPE_1__ i; void* net_done_jif; void* acked_jif; int /*<<< orphan*/  req_pending_local; int /*<<< orphan*/  completion_ref; struct drbd_device* device; } ;
struct drbd_peer_device {int dummy; } ;
struct drbd_device {int /*<<< orphan*/  misc_wait; int /*<<< orphan*/  ap_in_flight; } ;
struct bio_and_error {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_ASSERT (struct drbd_device*,unsigned int) ; 
 unsigned int RQ_COMPLETION_SUSP ; 
 unsigned int RQ_EXP_BARR_ACK ; 
 unsigned int RQ_LOCAL_ABORTED ; 
 unsigned int RQ_LOCAL_PENDING ; 
 unsigned int RQ_NET_DONE ; 
 unsigned int RQ_NET_PENDING ; 
 unsigned int RQ_NET_QUEUED ; 
 unsigned int RQ_NET_SENT ; 
 int /*<<< orphan*/  advance_conn_req_ack_pending (struct drbd_peer_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  advance_conn_req_next (struct drbd_peer_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  advance_conn_req_not_net_done (struct drbd_peer_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  atomic_add (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_sub (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dec_ap_pending (struct drbd_device*) ; 
 int /*<<< orphan*/  drbd_req_destroy ; 
 int /*<<< orphan*/  drbd_req_put_completion_ref (struct drbd_request*,struct bio_and_error*,int) ; 
 scalar_t__ drbd_suspended (struct drbd_device*) ; 
 struct drbd_peer_device* first_peer_device (struct drbd_device*) ; 
 int /*<<< orphan*/  inc_ap_pending (struct drbd_device*) ; 
 void* jiffies ; 
 int /*<<< orphan*/  kref_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kref_put (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_if_null_req_ack_pending (struct drbd_peer_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  set_if_null_req_next (struct drbd_peer_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  set_if_null_req_not_net_done (struct drbd_peer_device*,struct drbd_request*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mod_rq_state(struct drbd_request *req, struct bio_and_error *m,
		int clear, int set)
{
	struct drbd_device *device = req->device;
	struct drbd_peer_device *peer_device = first_peer_device(device);
	unsigned s = req->rq_state;
	int c_put = 0;

	if (drbd_suspended(device) && !((s | clear) & RQ_COMPLETION_SUSP))
		set |= RQ_COMPLETION_SUSP;

	/* apply */

	req->rq_state &= ~clear;
	req->rq_state |= set;

	/* no change? */
	if (req->rq_state == s)
		return;

	/* intent: get references */

	kref_get(&req->kref);

	if (!(s & RQ_LOCAL_PENDING) && (set & RQ_LOCAL_PENDING))
		atomic_inc(&req->completion_ref);

	if (!(s & RQ_NET_PENDING) && (set & RQ_NET_PENDING)) {
		inc_ap_pending(device);
		atomic_inc(&req->completion_ref);
	}

	if (!(s & RQ_NET_QUEUED) && (set & RQ_NET_QUEUED)) {
		atomic_inc(&req->completion_ref);
		set_if_null_req_next(peer_device, req);
	}

	if (!(s & RQ_EXP_BARR_ACK) && (set & RQ_EXP_BARR_ACK))
		kref_get(&req->kref); /* wait for the DONE */

	if (!(s & RQ_NET_SENT) && (set & RQ_NET_SENT)) {
		/* potentially already completed in the ack_receiver thread */
		if (!(s & RQ_NET_DONE)) {
			atomic_add(req->i.size >> 9, &device->ap_in_flight);
			set_if_null_req_not_net_done(peer_device, req);
		}
		if (req->rq_state & RQ_NET_PENDING)
			set_if_null_req_ack_pending(peer_device, req);
	}

	if (!(s & RQ_COMPLETION_SUSP) && (set & RQ_COMPLETION_SUSP))
		atomic_inc(&req->completion_ref);

	/* progress: put references */

	if ((s & RQ_COMPLETION_SUSP) && (clear & RQ_COMPLETION_SUSP))
		++c_put;

	if (!(s & RQ_LOCAL_ABORTED) && (set & RQ_LOCAL_ABORTED)) {
		D_ASSERT(device, req->rq_state & RQ_LOCAL_PENDING);
		++c_put;
	}

	if ((s & RQ_LOCAL_PENDING) && (clear & RQ_LOCAL_PENDING)) {
		if (req->rq_state & RQ_LOCAL_ABORTED)
			kref_put(&req->kref, drbd_req_destroy);
		else
			++c_put;
		list_del_init(&req->req_pending_local);
	}

	if ((s & RQ_NET_PENDING) && (clear & RQ_NET_PENDING)) {
		dec_ap_pending(device);
		++c_put;
		req->acked_jif = jiffies;
		advance_conn_req_ack_pending(peer_device, req);
	}

	if ((s & RQ_NET_QUEUED) && (clear & RQ_NET_QUEUED)) {
		++c_put;
		advance_conn_req_next(peer_device, req);
	}

	if (!(s & RQ_NET_DONE) && (set & RQ_NET_DONE)) {
		if (s & RQ_NET_SENT)
			atomic_sub(req->i.size >> 9, &device->ap_in_flight);
		if (s & RQ_EXP_BARR_ACK)
			kref_put(&req->kref, drbd_req_destroy);
		req->net_done_jif = jiffies;

		/* in ahead/behind mode, or just in case,
		 * before we finally destroy this request,
		 * the caching pointers must not reference it anymore */
		advance_conn_req_next(peer_device, req);
		advance_conn_req_ack_pending(peer_device, req);
		advance_conn_req_not_net_done(peer_device, req);
	}

	/* potentially complete and destroy */

	/* If we made progress, retry conflicting peer requests, if any. */
	if (req->i.waiting)
		wake_up(&device->misc_wait);

	drbd_req_put_completion_ref(req, m, c_put);
	kref_put(&req->kref, drbd_req_destroy);
}