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
struct module_env {scalar_t__ worker; } ;
struct auth_xfer {int /*<<< orphan*/  lock; TYPE_2__* task_nextprobe; int /*<<< orphan*/  name; TYPE_1__* task_transfer; } ;
struct TYPE_4__ {int /*<<< orphan*/ * worker; } ;
struct TYPE_3__ {scalar_t__ worker; int /*<<< orphan*/  master; scalar_t__ lookup_target; } ;

/* Variables and functions */
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  xfr_set_timeout (struct auth_xfer*,struct module_env*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfr_transfer_current_master (struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_transfer_disown (struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_transfer_end_of_list (struct auth_xfer*) ; 
 scalar_t__ xfr_transfer_init_fetch (struct auth_xfer*,struct module_env*) ; 
 scalar_t__ xfr_transfer_lookup_host (struct auth_xfer*,struct module_env*) ; 
 int /*<<< orphan*/  xfr_transfer_move_to_next_lookup (struct auth_xfer*,struct module_env*) ; 
 int /*<<< orphan*/  xfr_transfer_nextmaster (struct auth_xfer*) ; 

__attribute__((used)) static void
xfr_transfer_nexttarget_or_end(struct auth_xfer* xfr, struct module_env* env)
{
	log_assert(xfr->task_transfer->worker == env->worker);

	/* are we performing lookups? */
	while(xfr->task_transfer->lookup_target) {
		if(xfr_transfer_lookup_host(xfr, env)) {
			/* wait for lookup to finish,
			 * note that the hostname may be in unbound's cache
			 * and we may then get an instant cache response,
			 * and that calls the callback just like a full
			 * lookup and lookup failures also call callback */
			if(verbosity >= VERB_ALGO) {
				char zname[255+1];
				dname_str(xfr->name, zname);
				verbose(VERB_ALGO, "auth zone %s transfer next target lookup", zname);
			}
			lock_basic_unlock(&xfr->lock);
			return;
		}
		xfr_transfer_move_to_next_lookup(xfr, env);
	}

	/* initiate TCP and fetch the zone from the master */
	/* and set timeout on it */
	while(!xfr_transfer_end_of_list(xfr)) {
		xfr->task_transfer->master = xfr_transfer_current_master(xfr);
		if(xfr_transfer_init_fetch(xfr, env)) {
			/* successfully started, wait for callback */
			lock_basic_unlock(&xfr->lock);
			return;
		}
		/* failed to fetch, next master */
		xfr_transfer_nextmaster(xfr);
	}
	if(verbosity >= VERB_ALGO) {
		char zname[255+1];
		dname_str(xfr->name, zname);
		verbose(VERB_ALGO, "auth zone %s transfer failed, wait", zname);
	}

	/* we failed to fetch the zone, move to wait task
	 * use the shorter retry timeout */
	xfr_transfer_disown(xfr);

	/* pick up the nextprobe task and wait */
	if(xfr->task_nextprobe->worker == NULL)
		xfr_set_timeout(xfr, env, 1, 0);
	lock_basic_unlock(&xfr->lock);
}