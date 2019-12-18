#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct thread {int dummy; } ;
struct nlm_host {int nh_sysid; int nh_state; scalar_t__ nh_monstate; int /*<<< orphan*/  nh_caller_name; int /*<<< orphan*/  nh_refs; int /*<<< orphan*/  nh_lock; int /*<<< orphan*/  nh_pending; } ;
struct nlm_async_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_DEBUG (int,char*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ NLM_RECOVERING ; 
 int NLM_SYSID_CLIENT ; 
 struct nlm_async_lock* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  curproc ; 
 int /*<<< orphan*/  kthread_add (int /*<<< orphan*/ ,struct nlm_host*,int /*<<< orphan*/ ,struct thread**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lf_clearremotesys (int) ; 
 scalar_t__ lf_countlocks (int) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_cancel_async_lock (struct nlm_async_lock*) ; 
 int /*<<< orphan*/  nlm_check_expired_locks (struct nlm_host*) ; 
 int /*<<< orphan*/  nlm_client_recovery_start ; 
 int /*<<< orphan*/  refcount_acquire (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nlm_host_notify(struct nlm_host *host, int newstate)
{
	struct nlm_async_lock *af;

	if (newstate) {
		NLM_DEBUG(1, "NLM: host %s (sysid %d) rebooted, new "
		    "state is %d\n", host->nh_caller_name,
		    host->nh_sysid, newstate);
	}

	/*
	 * Cancel any pending async locks for this host.
	 */
	mtx_lock(&host->nh_lock);
	while ((af = TAILQ_FIRST(&host->nh_pending)) != NULL) {
		/*
		 * nlm_cancel_async_lock will remove the entry from
		 * nh_pending and free it.
		 */
		nlm_cancel_async_lock(af);
	}
	mtx_unlock(&host->nh_lock);
	nlm_check_expired_locks(host);

	/*
	 * The host just rebooted - trash its locks.
	 */
	lf_clearremotesys(host->nh_sysid);
	host->nh_state = newstate;

	/*
	 * If we have any remote locks for this host (i.e. it
	 * represents a remote NFS server that our local NFS client
	 * has locks for), start a recovery thread.
	 */
	if (newstate != 0
	    && host->nh_monstate != NLM_RECOVERING
	    && lf_countlocks(NLM_SYSID_CLIENT | host->nh_sysid) > 0) {
		struct thread *td;
		host->nh_monstate = NLM_RECOVERING;
		refcount_acquire(&host->nh_refs);
		kthread_add(nlm_client_recovery_start, host, curproc, &td, 0, 0,
		    "NFS lock recovery for %s", host->nh_caller_name);
	}
}