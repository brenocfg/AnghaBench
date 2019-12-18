#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct module_env {TYPE_1__* outnet; } ;
struct comm_reply {int /*<<< orphan*/ * c; } ;
struct comm_point {int tcp_is_reading; int /*<<< orphan*/  buffer; } ;
struct auth_xfer {int /*<<< orphan*/  lock; TYPE_3__* task_transfer; } ;
struct TYPE_7__ {int /*<<< orphan*/ * cp; TYPE_2__* master; int /*<<< orphan*/  timer; struct module_env* env; } ;
struct TYPE_6__ {int host; } ;
struct TYPE_5__ {scalar_t__ want_to_quit; } ;

/* Variables and functions */
 int /*<<< orphan*/  AUTH_TRANSFER_TIMEOUT ; 
 int NETEVENT_DONE ; 
 int NETEVENT_NOERROR ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  auth_chunks_delete (TYPE_3__*) ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  comm_point_start_listening (struct comm_point*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  comm_timer_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  process_list_end_transfer (struct auth_xfer*,struct module_env*) ; 
 int /*<<< orphan*/  sldns_buffer_clear (int /*<<< orphan*/ ) ; 
 scalar_t__ sldns_buffer_limit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  xfer_link_data (int /*<<< orphan*/ ,struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_transfer_nextmaster (struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_transfer_nexttarget_or_end (struct auth_xfer*,struct module_env*) ; 

int
auth_xfer_transfer_http_callback(struct comm_point* c, void* arg, int err,
	struct comm_reply* repinfo)
{
	struct auth_xfer* xfr = (struct auth_xfer*)arg;
	struct module_env* env;
	log_assert(xfr->task_transfer);
	lock_basic_lock(&xfr->lock);
	env = xfr->task_transfer->env;
	if(env->outnet->want_to_quit) {
		lock_basic_unlock(&xfr->lock);
		return 0; /* stop on quit */
	}
	verbose(VERB_ALGO, "auth zone transfer http callback");
	/* stop the timer */
	comm_timer_disable(xfr->task_transfer->timer);

	if(err != NETEVENT_NOERROR && err != NETEVENT_DONE) {
		/* connection failed, closed, or timeout */
		/* stop this transfer, cleanup 
		 * and continue task_transfer*/
		verbose(VERB_ALGO, "http stopped, connection lost to %s",
			xfr->task_transfer->master->host);
	failed:
		/* delete transferred data from list */
		auth_chunks_delete(xfr->task_transfer);
		if(repinfo) repinfo->c = NULL; /* signal cp deleted to
				the routine calling this callback */
		comm_point_delete(xfr->task_transfer->cp);
		xfr->task_transfer->cp = NULL;
		xfr_transfer_nextmaster(xfr);
		xfr_transfer_nexttarget_or_end(xfr, env);
		return 0;
	}

	/* if it is good, link it into the list of data */
	/* if the link into list of data fails (malloc fail) cleanup and end */
	if(sldns_buffer_limit(c->buffer) > 0) {
		verbose(VERB_ALGO, "auth zone http queued up %d bytes",
			(int)sldns_buffer_limit(c->buffer));
		if(!xfer_link_data(c->buffer, xfr)) {
			verbose(VERB_ALGO, "http stopped to %s, malloc failed",
				xfr->task_transfer->master->host);
			goto failed;
		}
	}
	/* if the transfer is done now, disconnect and process the list */
	if(err == NETEVENT_DONE) {
		if(repinfo) repinfo->c = NULL; /* signal cp deleted to
				the routine calling this callback */
		comm_point_delete(xfr->task_transfer->cp);
		xfr->task_transfer->cp = NULL;
		process_list_end_transfer(xfr, env);
		return 0;
	}

	/* if we want to read more messages, setup the commpoint to read
	 * a DNS packet, and the timeout */
	lock_basic_unlock(&xfr->lock);
	c->tcp_is_reading = 1;
	sldns_buffer_clear(c->buffer);
	comm_point_start_listening(c, -1, AUTH_TRANSFER_TIMEOUT);
	return 0;
}