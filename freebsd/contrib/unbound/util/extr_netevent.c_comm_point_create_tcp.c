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
struct tcl_list {int dummy; } ;
struct sldns_buffer {int dummy; } ;
struct internal_event {int fd; int tcp_timeout_msec; int max_tcp_count; struct internal_event** tcp_handlers; int /*<<< orphan*/ * timeout; struct internal_event* ev; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/ * callback; int /*<<< orphan*/ * dnscrypt_buffer; scalar_t__ dnscrypt; scalar_t__ tcp_do_fastopen; scalar_t__ tcp_check_nb_connect; scalar_t__ tcp_do_toggle_rw; scalar_t__ do_not_close; scalar_t__ tcp_do_close; int /*<<< orphan*/  type; int /*<<< orphan*/ * tcp_free; scalar_t__ cur_tcp_count; int /*<<< orphan*/ * tcp_parent; scalar_t__ tcp_keepalive; int /*<<< orphan*/ * tcl_addr; struct tcl_list* tcp_conn_limit; scalar_t__ tcp_byte_count; scalar_t__ tcp_is_reading; int /*<<< orphan*/ * buffer; struct comm_base* base; } ;
struct comm_point {int fd; int tcp_timeout_msec; int max_tcp_count; struct comm_point** tcp_handlers; int /*<<< orphan*/ * timeout; struct comm_point* ev; int /*<<< orphan*/ * cb_arg; int /*<<< orphan*/ * callback; int /*<<< orphan*/ * dnscrypt_buffer; scalar_t__ dnscrypt; scalar_t__ tcp_do_fastopen; scalar_t__ tcp_check_nb_connect; scalar_t__ tcp_do_toggle_rw; scalar_t__ do_not_close; scalar_t__ tcp_do_close; int /*<<< orphan*/  type; int /*<<< orphan*/ * tcp_free; scalar_t__ cur_tcp_count; int /*<<< orphan*/ * tcp_parent; scalar_t__ tcp_keepalive; int /*<<< orphan*/ * tcl_addr; struct tcl_list* tcp_conn_limit; scalar_t__ tcp_byte_count; scalar_t__ tcp_is_reading; int /*<<< orphan*/ * buffer; struct comm_base* base; } ;
struct comm_base {TYPE_1__* eb; } ;
typedef  int /*<<< orphan*/  comm_point_callback_type ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 short UB_EV_PERSIST ; 
 short UB_EV_READ ; 
 scalar_t__ calloc (size_t,int) ; 
 struct internal_event* comm_point_create_tcp_handler (struct comm_base*,struct internal_event*,size_t,struct sldns_buffer*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  comm_point_delete (struct internal_event*) ; 
 int /*<<< orphan*/  comm_point_tcp_accept_callback ; 
 int /*<<< orphan*/  comm_tcp_accept ; 
 int /*<<< orphan*/  free (struct internal_event*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ ub_event_add (struct internal_event*,int /*<<< orphan*/ *) ; 
 struct internal_event* ub_event_new (int /*<<< orphan*/ ,int,short,int /*<<< orphan*/ ,struct internal_event*) ; 

struct comm_point* 
comm_point_create_tcp(struct comm_base *base, int fd, int num,
	int idle_timeout, struct tcl_list* tcp_conn_limit, size_t bufsize,
	struct sldns_buffer* spoolbuf, comm_point_callback_type* callback,
	void* callback_arg)
{
	struct comm_point* c = (struct comm_point*)calloc(1,
		sizeof(struct comm_point));
	short evbits;
	int i;
	/* first allocate the TCP accept listener */
	if(!c)
		return NULL;
	c->ev = (struct internal_event*)calloc(1,
		sizeof(struct internal_event));
	if(!c->ev) {
		free(c);
		return NULL;
	}
	c->ev->base = base;
	c->fd = fd;
	c->buffer = NULL;
	c->timeout = NULL;
	c->tcp_is_reading = 0;
	c->tcp_byte_count = 0;
	c->tcp_timeout_msec = idle_timeout;
	c->tcp_conn_limit = tcp_conn_limit;
	c->tcl_addr = NULL;
	c->tcp_keepalive = 0;
	c->tcp_parent = NULL;
	c->max_tcp_count = num;
	c->cur_tcp_count = 0;
	c->tcp_handlers = (struct comm_point**)calloc((size_t)num,
		sizeof(struct comm_point*));
	if(!c->tcp_handlers) {
		free(c->ev);
		free(c);
		return NULL;
	}
	c->tcp_free = NULL;
	c->type = comm_tcp_accept;
	c->tcp_do_close = 0;
	c->do_not_close = 0;
	c->tcp_do_toggle_rw = 0;
	c->tcp_check_nb_connect = 0;
#ifdef USE_MSG_FASTOPEN
	c->tcp_do_fastopen = 0;
#endif
#ifdef USE_DNSCRYPT
	c->dnscrypt = 0;
	c->dnscrypt_buffer = NULL;
#endif
	c->callback = NULL;
	c->cb_arg = NULL;
	evbits = UB_EV_READ | UB_EV_PERSIST;
	/* ub_event stuff */
	c->ev->ev = ub_event_new(base->eb->base, c->fd, evbits,
		comm_point_tcp_accept_callback, c);
	if(c->ev->ev == NULL) {
		log_err("could not baseset tcpacc event");
		comm_point_delete(c);
		return NULL;
	}
	if (ub_event_add(c->ev->ev, c->timeout) != 0) {
		log_err("could not add tcpacc event");
		comm_point_delete(c);
		return NULL;
	}
	/* now prealloc the tcp handlers */
	for(i=0; i<num; i++) {
		c->tcp_handlers[i] = comm_point_create_tcp_handler(base,
			c, bufsize, spoolbuf, callback, callback_arg);
		if(!c->tcp_handlers[i]) {
			comm_point_delete(c);
			return NULL;
		}
	}
	
	return c;
}