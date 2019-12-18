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
struct comm_point {scalar_t__ type; scalar_t__ ssl_shake_state; int tcp_is_reading; scalar_t__ tcp_byte_count; scalar_t__ tcp_do_toggle_rw; int /*<<< orphan*/  buffer; scalar_t__ ssl; scalar_t__ tcp_check_nb_connect; } ;

/* Variables and functions */
 scalar_t__ comm_http ; 
 int /*<<< orphan*/  comm_point_start_listening (struct comm_point*,int,int) ; 
 int /*<<< orphan*/  comm_point_stop_listening (struct comm_point*) ; 
 scalar_t__ comm_ssl_shake_none ; 
 int http_check_connect (int,struct comm_point*) ; 
 int /*<<< orphan*/  http_write_more (int,struct comm_point*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_remaining (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ssl_handshake (struct comm_point*) ; 
 int /*<<< orphan*/  ssl_http_write_more (struct comm_point*) ; 

__attribute__((used)) static int
comm_point_http_handle_write(int fd, struct comm_point* c)
{
	log_assert(c->type == comm_http);
	log_assert(fd != -1);

	/* check pending connect errors, if that fails, we wait for more,
	 * or we can continue to write contents */
	if(c->tcp_check_nb_connect) {
		int r = http_check_connect(fd, c);
		if(r == 0) return 0;
		if(r == 1) return 1;
		c->tcp_check_nb_connect = 0;
	}
	/* if we are in ssl handshake, handle SSL handshake */
#ifdef HAVE_SSL
	if(c->ssl && c->ssl_shake_state != comm_ssl_shake_none) {
		if(!ssl_handshake(c))
			return 0;
		if(c->ssl_shake_state != comm_ssl_shake_none)
			return 1;
	}
#endif /* HAVE_SSL */
	if(c->tcp_is_reading)
		return 1;
	/* if we are writing, write more */
	if(c->ssl) {
		if(!ssl_http_write_more(c))
			return 0;
	} else {
		if(!http_write_more(fd, c))
			return 0;
	}

	/* we write a single buffer contents, that can contain
	 * the http request, and then flip to read the results */
	/* see if write is done */
	if(sldns_buffer_remaining(c->buffer) == 0) {
		sldns_buffer_clear(c->buffer);
		if(c->tcp_do_toggle_rw)
			c->tcp_is_reading = 1;
		c->tcp_byte_count = 0;
		/* switch from listening(write) to listening(read) */
		comm_point_stop_listening(c);
		comm_point_start_listening(c, -1, -1);
	}
	return 1;
}