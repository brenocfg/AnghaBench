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
struct tcp_req_info {int in_worker_handle; scalar_t__ is_reply; scalar_t__ is_drop; int /*<<< orphan*/  spool_buffer; struct comm_point* cp; } ;
struct comm_point {int /*<<< orphan*/  buffer; int /*<<< orphan*/  tcp_timeout_msec; scalar_t__ tcp_is_reading; int /*<<< orphan*/  repinfo; int /*<<< orphan*/  cb_arg; scalar_t__ (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_NOERROR ; 
 int /*<<< orphan*/  comm_point_start_listening (struct comm_point*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_stop_listening (struct comm_point*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (scalar_t__ (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_set_limit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_req_info_setup_listen (struct tcp_req_info*) ; 
 int /*<<< orphan*/  tcp_req_pickup_next_result (struct tcp_req_info*) ; 

void
tcp_req_info_handle_readdone(struct tcp_req_info* req)
{
	struct comm_point* c = req->cp;

	/* we want to read up several requests, unless there are
	 * pending answers */

	req->is_drop = 0;
	req->is_reply = 0;
	req->in_worker_handle = 1;
	sldns_buffer_set_limit(req->spool_buffer, 0);
	/* handle the current request */
	/* this calls the worker handle request routine that could give
	 * a cache response, or localdata response, or drop the reply,
	 * or schedule a mesh entry for later */
	fptr_ok(fptr_whitelist_comm_point(c->callback));
	if( (*c->callback)(c, c->cb_arg, NETEVENT_NOERROR, &c->repinfo) ) {
		req->in_worker_handle = 0;
		/* there is an answer, put it up.  It is already in the
		 * c->buffer, just send it. */
		/* since we were just reading a query, the channel is
		 * clear to write to */
	send_it:
		c->tcp_is_reading = 0;
		comm_point_stop_listening(c);
		comm_point_start_listening(c, -1, c->tcp_timeout_msec);
		return;
	}
	req->in_worker_handle = 0;
	/* it should be waiting in the mesh for recursion.
	 * If mesh failed to add a new entry and called commpoint_drop_reply. 
	 * Then the mesh state has been cleared. */
	if(req->is_drop) {
		/* the reply has been dropped, stream has been closed. */
		return;
	}
	/* If mesh failed(mallocfail) and called commpoint_send_reply with
	 * something like servfail then we pick up that reply below. */
	if(req->is_reply) {
		goto send_it;
	}

	sldns_buffer_clear(c->buffer);
	/* if pending answers, pick up an answer and start sending it */
	tcp_req_pickup_next_result(req);

	/* if answers pending, start sending answers */
	/* read more requests if we can have more requests */
	tcp_req_info_setup_listen(req);
}