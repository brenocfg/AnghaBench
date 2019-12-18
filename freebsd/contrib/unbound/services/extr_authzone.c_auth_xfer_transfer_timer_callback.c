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
struct auth_xfer {TYPE_3__* task_transfer; int /*<<< orphan*/  lock; } ;
struct TYPE_7__ {scalar_t__ ixfr_possible_timeout_count; int ixfr_fail; int /*<<< orphan*/ * cp; TYPE_2__* master; scalar_t__ on_ixfr; struct module_env* env; } ;
struct TYPE_6__ {int /*<<< orphan*/  host; } ;
struct TYPE_5__ {scalar_t__ want_to_quit; } ;

/* Variables and functions */
 scalar_t__ NUM_TIMEOUTS_FALLBACK_IXFR ; 
 int /*<<< orphan*/  VERB_ALGO ; 
 int /*<<< orphan*/  auth_chunks_delete (TYPE_3__*) ; 
 int /*<<< orphan*/  comm_point_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (TYPE_3__*) ; 
 int /*<<< orphan*/  verbose (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfr_transfer_nextmaster (struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_transfer_nexttarget_or_end (struct auth_xfer*,struct module_env*) ; 

void
auth_xfer_transfer_timer_callback(void* arg)
{
	struct auth_xfer* xfr = (struct auth_xfer*)arg;
	struct module_env* env;
	int gonextonfail = 1;
	log_assert(xfr->task_transfer);
	lock_basic_lock(&xfr->lock);
	env = xfr->task_transfer->env;
	if(env->outnet->want_to_quit) {
		lock_basic_unlock(&xfr->lock);
		return; /* stop on quit */
	}

	verbose(VERB_ALGO, "xfr stopped, connection timeout to %s",
		xfr->task_transfer->master->host);

	/* see if IXFR caused the failure, if so, try AXFR */
	if(xfr->task_transfer->on_ixfr) {
		xfr->task_transfer->ixfr_possible_timeout_count++;
		if(xfr->task_transfer->ixfr_possible_timeout_count >=
			NUM_TIMEOUTS_FALLBACK_IXFR) {
			verbose(VERB_ALGO, "xfr to %s, fallback "
				"from IXFR to AXFR (because of timeouts)",
				xfr->task_transfer->master->host);
			xfr->task_transfer->ixfr_fail = 1;
			gonextonfail = 0;
		}
	}

	/* delete transferred data from list */
	auth_chunks_delete(xfr->task_transfer);
	comm_point_delete(xfr->task_transfer->cp);
	xfr->task_transfer->cp = NULL;
	if(gonextonfail)
		xfr_transfer_nextmaster(xfr);
	xfr_transfer_nexttarget_or_end(xfr, env);
}