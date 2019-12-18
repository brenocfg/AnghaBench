#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct comm_point {scalar_t__ type; scalar_t__ dnscrypt_buffer; scalar_t__ buffer; TYPE_3__* tcp_req_info; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  tcp_do_close; scalar_t__ dnscrypt; TYPE_2__* tcp_parent; TYPE_1__* ev; } ;
struct TYPE_6__ {scalar_t__ read_again; } ;
struct TYPE_5__ {scalar_t__ dnscrypt; } ;
struct TYPE_4__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_CLOSED ; 
 int /*<<< orphan*/  NETEVENT_TIMEOUT ; 
 short UB_EV_READ ; 
 short UB_EV_TIMEOUT ; 
 short UB_EV_WRITE ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 int /*<<< orphan*/  comm_point_tcp_handle_read (int,struct comm_point*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_point_tcp_handle_write (int,struct comm_point*) ; 
 scalar_t__ comm_tcp ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*,...) ; 
 int /*<<< orphan*/  reclaim_tcp_handler (struct comm_point*) ; 
 int /*<<< orphan*/  sldns_buffer_capacity (scalar_t__) ; 
 scalar_t__ sldns_buffer_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub4 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_req_info_read_again (int,struct comm_point*) ; 
 int /*<<< orphan*/  ub_comm_base_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void 
comm_point_tcp_handle_callback(int fd, short event, void* arg)
{
	struct comm_point* c = (struct comm_point*)arg;
	log_assert(c->type == comm_tcp);
	ub_comm_base_now(c->ev->base);

#ifdef USE_DNSCRYPT
	/* Initialize if this is a dnscrypt socket */
	if(c->tcp_parent) {
		c->dnscrypt = c->tcp_parent->dnscrypt;
	}
	if(c->dnscrypt && c->dnscrypt_buffer == c->buffer) {
		c->dnscrypt_buffer = sldns_buffer_new(sldns_buffer_capacity(c->buffer));
		if(!c->dnscrypt_buffer) {
			log_err("Could not allocate dnscrypt buffer");
			reclaim_tcp_handler(c);
			if(!c->tcp_do_close) {
				fptr_ok(fptr_whitelist_comm_point(
					c->callback));
				(void)(*c->callback)(c, c->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
			return;
		}
	}
#endif

	if(event&UB_EV_TIMEOUT) {
		verbose(VERB_QUERY, "tcp took too long, dropped");
		reclaim_tcp_handler(c);
		if(!c->tcp_do_close) {
			fptr_ok(fptr_whitelist_comm_point(c->callback));
			(void)(*c->callback)(c, c->cb_arg,
				NETEVENT_TIMEOUT, NULL);
		}
		return;
	}
	if(event&UB_EV_READ) {
		int has_tcpq = (c->tcp_req_info != NULL);
		if(!comm_point_tcp_handle_read(fd, c, 0)) {
			reclaim_tcp_handler(c);
			if(!c->tcp_do_close) {
				fptr_ok(fptr_whitelist_comm_point(
					c->callback));
				(void)(*c->callback)(c, c->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
		}
		if(has_tcpq && c->tcp_req_info && c->tcp_req_info->read_again)
			tcp_req_info_read_again(fd, c);
		return;
	}
	if(event&UB_EV_WRITE) {
		int has_tcpq = (c->tcp_req_info != NULL);
		if(!comm_point_tcp_handle_write(fd, c)) {
			reclaim_tcp_handler(c);
			if(!c->tcp_do_close) {
				fptr_ok(fptr_whitelist_comm_point(
					c->callback));
				(void)(*c->callback)(c, c->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
		}
		if(has_tcpq && c->tcp_req_info && c->tcp_req_info->read_again)
			tcp_req_info_read_again(fd, c);
		return;
	}
	log_err("Ignored event %d for tcphdl.", event);
}