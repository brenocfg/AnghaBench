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
struct comm_point {scalar_t__ type; int /*<<< orphan*/  tcp_timeout_msec; int /*<<< orphan*/  repinfo; int /*<<< orphan*/  cb_arg; scalar_t__ (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;scalar_t__ tcp_req_info; scalar_t__ tcp_byte_count; scalar_t__ tcp_is_reading; scalar_t__ tcp_do_toggle_rw; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_NOERROR ; 
 scalar_t__ comm_local ; 
 int /*<<< orphan*/  comm_point_start_listening (struct comm_point*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_stop_listening (struct comm_point*) ; 
 scalar_t__ comm_tcp ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (scalar_t__ (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  sldns_buffer_flip (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_req_info_handle_readdone (scalar_t__) ; 

__attribute__((used)) static void
tcp_callback_reader(struct comm_point* c)
{
	log_assert(c->type == comm_tcp || c->type == comm_local);
	sldns_buffer_flip(c->buffer);
	if(c->tcp_do_toggle_rw)
		c->tcp_is_reading = 0;
	c->tcp_byte_count = 0;
	if(c->tcp_req_info) {
		tcp_req_info_handle_readdone(c->tcp_req_info);
	} else {
		if(c->type == comm_tcp)
			comm_point_stop_listening(c);
		fptr_ok(fptr_whitelist_comm_point(c->callback));
		if( (*c->callback)(c, c->cb_arg, NETEVENT_NOERROR, &c->repinfo) ) {
			comm_point_start_listening(c, -1, c->tcp_timeout_msec);
		}
	}
}