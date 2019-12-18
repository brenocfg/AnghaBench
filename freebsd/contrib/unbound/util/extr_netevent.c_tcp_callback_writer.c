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
struct comm_point {scalar_t__ type; int tcp_is_reading; scalar_t__ tcp_req_info; scalar_t__ tcp_byte_count; scalar_t__ tcp_do_toggle_rw; int /*<<< orphan*/  buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  comm_point_start_listening (struct comm_point*,int,int) ; 
 int /*<<< orphan*/  comm_point_stop_listening (struct comm_point*) ; 
 scalar_t__ comm_tcp ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_req_info_handle_writedone (scalar_t__) ; 

__attribute__((used)) static void
tcp_callback_writer(struct comm_point* c)
{
	log_assert(c->type == comm_tcp);
	sldns_buffer_clear(c->buffer);
	if(c->tcp_do_toggle_rw)
		c->tcp_is_reading = 1;
	c->tcp_byte_count = 0;
	/* switch from listening(write) to listening(read) */
	if(c->tcp_req_info) {
		tcp_req_info_handle_writedone(c->tcp_req_info);
	} else {
		comm_point_stop_listening(c);
		comm_point_start_listening(c, -1, -1);
	}
}