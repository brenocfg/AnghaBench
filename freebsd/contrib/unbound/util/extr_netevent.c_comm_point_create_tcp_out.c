#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {struct internal_event* c; } ;
struct internal_event {int fd; int tcp_do_toggle_rw; int tcp_check_nb_connect; int tcp_do_fastopen; struct internal_event* ev; scalar_t__ buffer; void* cb_arg; int /*<<< orphan*/ * callback; TYPE_1__ repinfo; scalar_t__ dnscrypt_buffer; scalar_t__ dnscrypt; scalar_t__ do_not_close; scalar_t__ tcp_do_close; int /*<<< orphan*/  type; int /*<<< orphan*/ * tcp_free; int /*<<< orphan*/ * tcp_handlers; scalar_t__ cur_tcp_count; scalar_t__ max_tcp_count; int /*<<< orphan*/ * tcp_parent; scalar_t__ tcp_keepalive; int /*<<< orphan*/ * tcl_addr; int /*<<< orphan*/ * tcp_conn_limit; int /*<<< orphan*/  tcp_timeout_msec; scalar_t__ tcp_byte_count; scalar_t__ tcp_is_reading; int /*<<< orphan*/ * timeout; struct comm_base* base; } ;
struct comm_point {int fd; int tcp_do_toggle_rw; int tcp_check_nb_connect; int tcp_do_fastopen; struct comm_point* ev; scalar_t__ buffer; void* cb_arg; int /*<<< orphan*/ * callback; TYPE_1__ repinfo; scalar_t__ dnscrypt_buffer; scalar_t__ dnscrypt; scalar_t__ do_not_close; scalar_t__ tcp_do_close; int /*<<< orphan*/  type; int /*<<< orphan*/ * tcp_free; int /*<<< orphan*/ * tcp_handlers; scalar_t__ cur_tcp_count; scalar_t__ max_tcp_count; int /*<<< orphan*/ * tcp_parent; scalar_t__ tcp_keepalive; int /*<<< orphan*/ * tcl_addr; int /*<<< orphan*/ * tcp_conn_limit; int /*<<< orphan*/  tcp_timeout_msec; scalar_t__ tcp_byte_count; scalar_t__ tcp_is_reading; int /*<<< orphan*/ * timeout; struct comm_base* base; } ;
struct comm_base {TYPE_2__* eb; } ;
typedef  int /*<<< orphan*/  comm_point_callback_type ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  TCP_QUERY_TIMEOUT ; 
 short UB_EV_PERSIST ; 
 short UB_EV_WRITE ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  comm_point_tcp_handle_callback ; 
 int /*<<< orphan*/  comm_tcp ; 
 int /*<<< orphan*/  free (struct internal_event*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 int /*<<< orphan*/  sldns_buffer_free (scalar_t__) ; 
 scalar_t__ sldns_buffer_new (size_t) ; 
 struct internal_event* ub_event_new (int /*<<< orphan*/ ,int,short,int /*<<< orphan*/ ,struct internal_event*) ; 

struct comm_point* 
comm_point_create_tcp_out(struct comm_base *base, size_t bufsize,
        comm_point_callback_type* callback, void* callback_arg)
{
	struct comm_point* c = (struct comm_point*)calloc(1,
		sizeof(struct comm_point));
	short evbits;
	if(!c)
		return NULL;
	c->ev = (struct internal_event*)calloc(1,
		sizeof(struct internal_event));
	if(!c->ev) {
		free(c);
		return NULL;
	}
	c->ev->base = base;
	c->fd = -1;
	c->buffer = sldns_buffer_new(bufsize);
	if(!c->buffer) {
		free(c->ev);
		free(c);
		return NULL;
	}
	c->timeout = NULL;
	c->tcp_is_reading = 0;
	c->tcp_byte_count = 0;
	c->tcp_timeout_msec = TCP_QUERY_TIMEOUT;
	c->tcp_conn_limit = NULL;
	c->tcl_addr = NULL;
	c->tcp_keepalive = 0;
	c->tcp_parent = NULL;
	c->max_tcp_count = 0;
	c->cur_tcp_count = 0;
	c->tcp_handlers = NULL;
	c->tcp_free = NULL;
	c->type = comm_tcp;
	c->tcp_do_close = 0;
	c->do_not_close = 0;
	c->tcp_do_toggle_rw = 1;
	c->tcp_check_nb_connect = 1;
#ifdef USE_MSG_FASTOPEN
	c->tcp_do_fastopen = 1;
#endif
#ifdef USE_DNSCRYPT
	c->dnscrypt = 0;
	c->dnscrypt_buffer = c->buffer;
#endif
	c->repinfo.c = c;
	c->callback = callback;
	c->cb_arg = callback_arg;
	evbits = UB_EV_PERSIST | UB_EV_WRITE;
	c->ev->ev = ub_event_new(base->eb->base, c->fd, evbits,
		comm_point_tcp_handle_callback, c);
	if(c->ev->ev == NULL)
	{
		log_err("could not baseset tcpout event");
		sldns_buffer_free(c->buffer);
		free(c->ev);
		free(c);
		return NULL;
	}

	return c;
}