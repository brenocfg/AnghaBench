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
struct tcp_req_info {scalar_t__ num_done_req; scalar_t__ num_open_req; int read_is_closed; TYPE_1__* cp; } ;
struct TYPE_2__ {scalar_t__ tcp_byte_count; int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  tcp_req_info_setup_listen (struct tcp_req_info*) ; 
 int /*<<< orphan*/  tcp_req_pickup_next_result (struct tcp_req_info*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int
tcp_req_info_handle_read_close(struct tcp_req_info* req)
{
	verbose(VERB_ALGO, "tcp channel read side closed %d", req->cp->fd);
	/* reset byte count for (potential) partial read */
	req->cp->tcp_byte_count = 0;
	/* if we still have results to write, pick up next and write it */
	if(req->num_done_req != 0) {
		tcp_req_pickup_next_result(req);
		tcp_req_info_setup_listen(req);
		return 1;
	}
	/* if nothing to do, this closes the connection */
	if(req->num_open_req == 0 && req->num_done_req == 0)
		return 0;
	/* otherwise, we must be waiting for dns resolve, wait with timeout */
	req->read_is_closed = 1;
	tcp_req_info_setup_listen(req);
	return 1;
}