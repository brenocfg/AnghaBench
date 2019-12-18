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
struct internal_event {int fd; int tcp_is_reading; int do_not_close; struct internal_event* ev; int /*<<< orphan*/ * timeout; void* cb_arg; int /*<<< orphan*/ * callback; scalar_t__ buffer; scalar_t__ dnscrypt_buffer; scalar_t__ dnscrypt; scalar_t__ tcp_do_fastopen; scalar_t__ tcp_check_nb_connect; scalar_t__ tcp_do_toggle_rw; scalar_t__ tcp_do_close; int /*<<< orphan*/  type; int /*<<< orphan*/ * tcp_free; int /*<<< orphan*/ * tcp_handlers; scalar_t__ cur_tcp_count; scalar_t__ max_tcp_count; int /*<<< orphan*/ * tcp_parent; scalar_t__ tcp_byte_count; struct comm_base* base; } ;
struct comm_point {int fd; int tcp_is_reading; int do_not_close; struct comm_point* ev; int /*<<< orphan*/ * timeout; void* cb_arg; int /*<<< orphan*/ * callback; scalar_t__ buffer; scalar_t__ dnscrypt_buffer; scalar_t__ dnscrypt; scalar_t__ tcp_do_fastopen; scalar_t__ tcp_check_nb_connect; scalar_t__ tcp_do_toggle_rw; scalar_t__ tcp_do_close; int /*<<< orphan*/  type; int /*<<< orphan*/ * tcp_free; int /*<<< orphan*/ * tcp_handlers; scalar_t__ cur_tcp_count; scalar_t__ max_tcp_count; int /*<<< orphan*/ * tcp_parent; scalar_t__ tcp_byte_count; struct comm_base* base; } ;
struct comm_base {TYPE_1__* eb; } ;
typedef  int /*<<< orphan*/  comm_point_callback_type ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 short UB_EV_PERSIST ; 
 short UB_EV_READ ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  comm_local ; 
 int /*<<< orphan*/  comm_point_local_handle_callback ; 
 int /*<<< orphan*/  free (struct internal_event*) ; 
 int /*<<< orphan*/  log_err (char*) ; 
 scalar_t__ sldns_buffer_new (size_t) ; 
 scalar_t__ ub_event_add (struct internal_event*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_event_free (struct internal_event*) ; 
 struct internal_event* ub_event_new (int /*<<< orphan*/ ,int,short,int /*<<< orphan*/ ,struct internal_event*) ; 

struct comm_point* 
comm_point_create_local(struct comm_base *base, int fd, size_t bufsize,
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
	c->fd = fd;
	c->buffer = sldns_buffer_new(bufsize);
	if(!c->buffer) {
		free(c->ev);
		free(c);
		return NULL;
	}
	c->timeout = NULL;
	c->tcp_is_reading = 1;
	c->tcp_byte_count = 0;
	c->tcp_parent = NULL;
	c->max_tcp_count = 0;
	c->cur_tcp_count = 0;
	c->tcp_handlers = NULL;
	c->tcp_free = NULL;
	c->type = comm_local;
	c->tcp_do_close = 0;
	c->do_not_close = 1;
	c->tcp_do_toggle_rw = 0;
	c->tcp_check_nb_connect = 0;
#ifdef USE_MSG_FASTOPEN
	c->tcp_do_fastopen = 0;
#endif
#ifdef USE_DNSCRYPT
	c->dnscrypt = 0;
	c->dnscrypt_buffer = c->buffer;
#endif
	c->callback = callback;
	c->cb_arg = callback_arg;
	/* ub_event stuff */
	evbits = UB_EV_PERSIST | UB_EV_READ;
	c->ev->ev = ub_event_new(base->eb->base, c->fd, evbits,
		comm_point_local_handle_callback, c);
	if(c->ev->ev == NULL) {
		log_err("could not baseset localhdl event");
		free(c->ev);
		free(c);
		return NULL;
	}
	if (ub_event_add(c->ev->ev, c->timeout) != 0) {
		log_err("could not add localhdl event");
		ub_event_free(c->ev->ev);
		free(c->ev);
		free(c);
		return NULL;
	}
	return c;
}