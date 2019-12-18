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
struct module_env {scalar_t__* now; TYPE_1__* outnet; } ;
struct auth_xfer {scalar_t__ lease_time; scalar_t__ expiry; int /*<<< orphan*/  lock; int /*<<< orphan*/  zone_expired; scalar_t__ have_zone; TYPE_2__* task_nextprobe; } ;
struct TYPE_4__ {struct module_env* env; } ;
struct TYPE_3__ {scalar_t__ want_to_quit; } ;

/* Variables and functions */
 int /*<<< orphan*/  auth_xfer_set_expired (struct auth_xfer*,struct module_env*,int) ; 
 int /*<<< orphan*/  lock_basic_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lock_basic_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_assert (TYPE_2__*) ; 
 int /*<<< orphan*/  xfr_nextprobe_disown (struct auth_xfer*) ; 
 int /*<<< orphan*/  xfr_start_probe (struct auth_xfer*,struct module_env*,int /*<<< orphan*/ *) ; 

void
auth_xfer_timer(void* arg)
{
	struct auth_xfer* xfr = (struct auth_xfer*)arg;
	struct module_env* env;
	log_assert(xfr->task_nextprobe);
	lock_basic_lock(&xfr->lock);
	env = xfr->task_nextprobe->env;
	if(env->outnet->want_to_quit) {
		lock_basic_unlock(&xfr->lock);
		return; /* stop on quit */
	}

	/* see if zone has expired, and if so, also set auth_zone expired */
	if(xfr->have_zone && !xfr->zone_expired &&
	   *env->now >= xfr->lease_time + xfr->expiry) {
		lock_basic_unlock(&xfr->lock);
		auth_xfer_set_expired(xfr, env, 1);
		lock_basic_lock(&xfr->lock);
	}

	xfr_nextprobe_disown(xfr);

	if(!xfr_start_probe(xfr, env, NULL)) {
		/* not started because already in progress */
		lock_basic_unlock(&xfr->lock);
	}
}