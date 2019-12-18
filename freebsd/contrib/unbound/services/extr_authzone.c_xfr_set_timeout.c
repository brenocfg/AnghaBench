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
typedef  scalar_t__ time_t ;
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct module_env {scalar_t__* now; int /*<<< orphan*/ * worker; int /*<<< orphan*/  worker_base; } ;
struct auth_xfer {scalar_t__ lease_time; scalar_t__ refresh; scalar_t__ retry; scalar_t__ expiry; TYPE_2__* task_nextprobe; int /*<<< orphan*/  name; TYPE_1__* task_probe; scalar_t__ have_zone; } ;
struct TYPE_4__ {scalar_t__ next_probe; int backoff; scalar_t__ timer; struct module_env* env; int /*<<< orphan*/ * worker; } ;
struct TYPE_3__ {int only_lookup; int /*<<< orphan*/ * worker; scalar_t__ masters; } ;

/* Variables and functions */
 int AUTH_TRANSFER_MAX_BACKOFF ; 
 scalar_t__ VERB_ALGO ; 
 int /*<<< orphan*/  auth_xfer_timer ; 
 scalar_t__ comm_timer_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct auth_xfer*) ; 
 int /*<<< orphan*/  comm_timer_set (scalar_t__,struct timeval*) ; 
 int /*<<< orphan*/  dname_str (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  log_assert (int) ; 
 int /*<<< orphan*/  log_err (char*,char*) ; 
 int /*<<< orphan*/  verbose (scalar_t__,char*,char*,int) ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void
xfr_set_timeout(struct auth_xfer* xfr, struct module_env* env,
	int failure, int lookup_only)
{
	struct timeval tv;
	log_assert(xfr->task_nextprobe != NULL);
	log_assert(xfr->task_nextprobe->worker == NULL ||
		xfr->task_nextprobe->worker == env->worker);
	/* normally, nextprobe = startoflease + refresh,
	 * but if expiry is sooner, use that one.
	 * after a failure, use the retry timer instead. */
	xfr->task_nextprobe->next_probe = *env->now;
	if(xfr->lease_time && !failure)
		xfr->task_nextprobe->next_probe = xfr->lease_time;
	
	if(!failure) {
		xfr->task_nextprobe->backoff = 0;
	} else {
		if(xfr->task_nextprobe->backoff == 0)
				xfr->task_nextprobe->backoff = 3;
		else	xfr->task_nextprobe->backoff *= 2;
		if(xfr->task_nextprobe->backoff > AUTH_TRANSFER_MAX_BACKOFF)
			xfr->task_nextprobe->backoff =
				AUTH_TRANSFER_MAX_BACKOFF;
	}

	if(xfr->have_zone) {
		time_t wait = xfr->refresh;
		if(failure) wait = xfr->retry;
		if(xfr->expiry < wait)
			xfr->task_nextprobe->next_probe += xfr->expiry;
		else	xfr->task_nextprobe->next_probe += wait;
		if(failure)
			xfr->task_nextprobe->next_probe +=
				xfr->task_nextprobe->backoff;
		/* put the timer exactly on expiry, if possible */
		if(xfr->lease_time && xfr->lease_time+xfr->expiry <
			xfr->task_nextprobe->next_probe &&
			xfr->lease_time+xfr->expiry > *env->now)
			xfr->task_nextprobe->next_probe =
				xfr->lease_time+xfr->expiry;
	} else {
		xfr->task_nextprobe->next_probe +=
			xfr->task_nextprobe->backoff;
	}

	if(!xfr->task_nextprobe->timer) {
		xfr->task_nextprobe->timer = comm_timer_create(
			env->worker_base, auth_xfer_timer, xfr);
		if(!xfr->task_nextprobe->timer) {
			/* failed to malloc memory. likely zone transfer
			 * also fails for that. skip the timeout */
			char zname[255+1];
			dname_str(xfr->name, zname);
			log_err("cannot allocate timer, no refresh for %s",
				zname);
			return;
		}
	}
	xfr->task_nextprobe->worker = env->worker;
	xfr->task_nextprobe->env = env;
	if(*(xfr->task_nextprobe->env->now) <= xfr->task_nextprobe->next_probe)
		tv.tv_sec = xfr->task_nextprobe->next_probe - 
			*(xfr->task_nextprobe->env->now);
	else	tv.tv_sec = 0;
	if(tv.tv_sec != 0 && lookup_only && xfr->task_probe->masters) {
		/* don't lookup_only, if lookup timeout is 0 anyway,
		 * or if we don't have masters to lookup */
		tv.tv_sec = 0;
		if(xfr->task_probe && xfr->task_probe->worker == NULL)
			xfr->task_probe->only_lookup = 1;
	}
	if(verbosity >= VERB_ALGO) {
		char zname[255+1];
		dname_str(xfr->name, zname);
		verbose(VERB_ALGO, "auth zone %s timeout in %d seconds",
			zname, (int)tv.tv_sec);
	}
	tv.tv_usec = 0;
	comm_timer_set(xfr->task_nextprobe->timer, &tv);
}