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
struct nlm_host {int /*<<< orphan*/  nh_lock; int /*<<< orphan*/  nh_finished; int /*<<< orphan*/  nh_granted; } ;
struct TYPE_4__ {int /*<<< orphan*/  cookie; } ;
struct nlm_async_lock {scalar_t__ af_expiretime; TYPE_2__ af_granted; TYPE_1__* af_host; } ;
struct TYPE_3__ {int /*<<< orphan*/  nh_sysid; int /*<<< orphan*/  nh_caller_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NLM_DEBUG (int,char*,struct nlm_async_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct nlm_async_lock* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nlm_async_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  af_link ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_cookie (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ng_sysid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_free_async_lock (struct nlm_async_lock*) ; 
 scalar_t__ time_uptime ; 

__attribute__((used)) static void
nlm_check_expired_locks(struct nlm_host *host)
{
	struct nlm_async_lock *af;
	time_t uptime = time_uptime;

	mtx_lock(&host->nh_lock);
	while ((af = TAILQ_FIRST(&host->nh_granted)) != NULL
	    && uptime >= af->af_expiretime) {
		NLM_DEBUG(2, "NLM: async lock %p for %s (sysid %d) expired,"
		    " cookie %d:%d\n", af, af->af_host->nh_caller_name,
		    af->af_host->nh_sysid, ng_sysid(&af->af_granted.cookie),
		    ng_cookie(&af->af_granted.cookie));
		TAILQ_REMOVE(&host->nh_granted, af, af_link);
		mtx_unlock(&host->nh_lock);
		nlm_free_async_lock(af);
		mtx_lock(&host->nh_lock);
	}
	while ((af = TAILQ_FIRST(&host->nh_finished)) != NULL) {
		TAILQ_REMOVE(&host->nh_finished, af, af_link);
		mtx_unlock(&host->nh_lock);
		nlm_free_async_lock(af);
		mtx_lock(&host->nh_lock);
	}
	mtx_unlock(&host->nh_lock);
}