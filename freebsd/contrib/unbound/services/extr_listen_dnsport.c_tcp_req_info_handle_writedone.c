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
struct tcp_req_info {scalar_t__ num_done_req; TYPE_1__* cp; scalar_t__ read_is_closed; } ;
struct TYPE_2__ {int tcp_is_reading; int /*<<< orphan*/  repinfo; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_drop_reply (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_req_info_setup_listen (struct tcp_req_info*) ; 
 int /*<<< orphan*/  tcp_req_pickup_next_result (struct tcp_req_info*) ; 

void
tcp_req_info_handle_writedone(struct tcp_req_info* req)
{
	/* back to reading state, we finished this write event */
	sldns_buffer_clear(req->cp->buffer);
	if(req->num_done_req == 0 && req->read_is_closed) {
		/* no more to write and nothing to read, close it */
		comm_point_drop_reply(&req->cp->repinfo);
		return;
	}
	req->cp->tcp_is_reading = 1;
	/* see if another result needs writing */
	tcp_req_pickup_next_result(req);

	/* see if there is more to write, if not stop_listening for writing */
	/* see if new requests are allowed, if so, start_listening
	 * for reading */
	tcp_req_info_setup_listen(req);
}