#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcp_req_info {scalar_t__ num_open_req; scalar_t__ num_done_req; int read_again; TYPE_1__* cp; int /*<<< orphan*/  read_is_closed; } ;
struct TYPE_4__ {scalar_t__ tcp_byte_count; int tcp_is_reading; int /*<<< orphan*/  tcp_timeout_msec; } ;

/* Variables and functions */
 scalar_t__ TCP_MAX_REQ_SIMULTANEOUS ; 
 int /*<<< orphan*/  comm_point_listen_for_rw (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_start_listening (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_stop_listening (TYPE_1__*) ; 

__attribute__((used)) static void
tcp_req_info_setup_listen(struct tcp_req_info* req)
{
	int wr = 0;
	int rd = 0;

	if(req->cp->tcp_byte_count != 0) {
		/* cannot change, halfway through */
		return;
	}

	if(!req->cp->tcp_is_reading)
		wr = 1;
	if(req->num_open_req + req->num_done_req < TCP_MAX_REQ_SIMULTANEOUS &&
		!req->read_is_closed)
		rd = 1;
	
	if(wr) {
		req->cp->tcp_is_reading = 0;
		comm_point_stop_listening(req->cp);
		comm_point_start_listening(req->cp, -1,
			req->cp->tcp_timeout_msec);
	} else if(rd) {
		req->cp->tcp_is_reading = 1;
		comm_point_stop_listening(req->cp);
		comm_point_start_listening(req->cp, -1,
			req->cp->tcp_timeout_msec);
		/* and also read it (from SSL stack buffers), so
		 * no event read event is expected since the remainder of
		 * the TLS frame is sitting in the buffers. */
		req->read_again = 1;
	} else {
		comm_point_stop_listening(req->cp);
		comm_point_start_listening(req->cp, -1,
			req->cp->tcp_timeout_msec);
		comm_point_listen_for_rw(req->cp, 0, 0);
	}
}