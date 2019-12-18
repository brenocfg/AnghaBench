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
struct comm_point {scalar_t__ type; int /*<<< orphan*/  cb_arg; int /*<<< orphan*/  (* callback ) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  tcp_do_close; TYPE_1__* ev; } ;
struct TYPE_2__ {int /*<<< orphan*/  base; } ;

/* Variables and functions */
 int /*<<< orphan*/  NETEVENT_CLOSED ; 
 int /*<<< orphan*/  NETEVENT_TIMEOUT ; 
 short UB_EV_READ ; 
 short UB_EV_TIMEOUT ; 
 short UB_EV_WRITE ; 
 int /*<<< orphan*/  VERB_QUERY ; 
 scalar_t__ comm_http ; 
 int /*<<< orphan*/  comm_point_http_handle_read (int,struct comm_point*) ; 
 int /*<<< orphan*/  comm_point_http_handle_write (int,struct comm_point*) ; 
 int /*<<< orphan*/  fptr_ok (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fptr_whitelist_comm_point (int /*<<< orphan*/  (*) (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*,short) ; 
 int /*<<< orphan*/  reclaim_http_handler (struct comm_point*) ; 
 int /*<<< orphan*/  stub1 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub3 (struct comm_point*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ub_comm_base_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*) ; 

void 
comm_point_http_handle_callback(int fd, short event, void* arg)
{
	struct comm_point* c = (struct comm_point*)arg;
	log_assert(c->type == comm_http);
	ub_comm_base_now(c->ev->base);

	if(event&UB_EV_TIMEOUT) {
		verbose(VERB_QUERY, "http took too long, dropped");
		reclaim_http_handler(c);
		if(!c->tcp_do_close) {
			fptr_ok(fptr_whitelist_comm_point(c->callback));
			(void)(*c->callback)(c, c->cb_arg,
				NETEVENT_TIMEOUT, NULL);
		}
		return;
	}
	if(event&UB_EV_READ) {
		if(!comm_point_http_handle_read(fd, c)) {
			reclaim_http_handler(c);
			if(!c->tcp_do_close) {
				fptr_ok(fptr_whitelist_comm_point(
					c->callback));
				(void)(*c->callback)(c, c->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
		}
		return;
	}
	if(event&UB_EV_WRITE) {
		if(!comm_point_http_handle_write(fd, c)) {
			reclaim_http_handler(c);
			if(!c->tcp_do_close) {
				fptr_ok(fptr_whitelist_comm_point(
					c->callback));
				(void)(*c->callback)(c, c->cb_arg, 
					NETEVENT_CLOSED, NULL);
			}
		}
		return;
	}
	log_err("Ignored event %d for httphdl.", event);
}