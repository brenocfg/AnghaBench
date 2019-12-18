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
struct module_env {TYPE_1__* outnet; } ;
struct auth_xfer {TYPE_2__* task_probe; int /*<<< orphan*/  lock; int /*<<< orphan*/  name; } ;
struct TYPE_4__ {int timeout; int /*<<< orphan*/ * cp; struct module_env* env; } ;
struct TYPE_3__ {scalar_t__ want_to_quit; } ;

/* Variables and functions */
 int AUTH_PROBE_TIMEOUT_STOP ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  xfr_probe_nextmaster (struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_probe_send_or_end (struct auth_xfer*,struct module_env*) ; 
 scalar_t__ xfr_probe_send_probe (struct auth_xfer*,struct module_env*,int) ; 

void
auth_xfer_probe_timer_callback(void* arg)
{
	struct auth_xfer* xfr = (struct auth_xfer*)arg;
	struct module_env* env;
	log_assert(xfr->task_probe);
	lock_basic_lock(&xfr->lock);
	env = xfr->task_probe->env;
	if(env->outnet->want_to_quit) {
		lock_basic_unlock(&xfr->lock);
		return; /* stop on quit */
	}

	if(verbosity >= VERB_ALGO) {
		char zname[255+1];
		dname_str(xfr->name, zname);
		verbose(VERB_ALGO, "auth zone %s soa probe timeout", zname);
	}
	if(xfr->task_probe->timeout <= AUTH_PROBE_TIMEOUT_STOP) {
		/* try again with bigger timeout */
		if(xfr_probe_send_probe(xfr, env, xfr->task_probe->timeout*2)) {
			lock_basic_unlock(&xfr->lock);
			return;
		}
	}
	/* delete commpoint so a new one is created, with a fresh port nr */
	comm_point_delete(xfr->task_probe->cp);
	xfr->task_probe->cp = NULL;

	/* too many timeouts (or fail to send), move to next or end */
	xfr_probe_nextmaster(xfr);
	xfr_probe_send_or_end(xfr, env);
}