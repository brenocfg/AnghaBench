#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tcp_req_info {int is_reply; TYPE_1__* cp; int /*<<< orphan*/  spool_buffer; scalar_t__ in_worker_handle; } ;
struct TYPE_3__ {scalar_t__ tcp_byte_count; int /*<<< orphan*/  repinfo; int /*<<< orphan*/  tcp_timeout_msec; scalar_t__ tcp_is_reading; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_drop_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_point_start_listening (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_stop_listening (TYPE_1__*) ; 
 int /*<<< orphan*/  sldns_buffer_begin (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sldns_buffer_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_req_info_add_result (struct tcp_req_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_req_info_start_write_buf (struct tcp_req_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
tcp_req_info_send_reply(struct tcp_req_info* req)
{
	if(req->in_worker_handle) {
		/* reply from mesh is in the spool_buffer */
		/* copy now, so that the spool buffer is free for other tasks
		 * before the callback is done */
		sldns_buffer_clear(req->cp->buffer);
		sldns_buffer_write(req->cp->buffer,
			sldns_buffer_begin(req->spool_buffer),
			sldns_buffer_limit(req->spool_buffer));
		sldns_buffer_flip(req->cp->buffer);
		req->is_reply = 1;
		return;
	}
	/* now that the query has been handled, that mesh_reply entry
	 * should be removed, from the tcp_req_info list,
	 * the mesh state cleanup removes then with region_cleanup and
	 * replies_sent true. */
	/* see if we can send it straight away (we are not doing
	 * anything else).  If so, copy to buffer and start */
	if(req->cp->tcp_is_reading && req->cp->tcp_byte_count == 0) {
		/* buffer is free, and was ready to read new query into,
		 * but we are now going to use it to send this answer */
		tcp_req_info_start_write_buf(req,
			sldns_buffer_begin(req->spool_buffer),
			sldns_buffer_limit(req->spool_buffer));
		/* switch to listen to write events */
		comm_point_stop_listening(req->cp);
		comm_point_start_listening(req->cp, -1,
			req->cp->tcp_timeout_msec);
		return;
	}
	/* queue up the answer behind the others already pending */
	if(!tcp_req_info_add_result(req, sldns_buffer_begin(req->spool_buffer),
		sldns_buffer_limit(req->spool_buffer))) {
		/* drop the connection, we are out of resources */
		comm_point_drop_reply(&req->cp->repinfo);
	}
}