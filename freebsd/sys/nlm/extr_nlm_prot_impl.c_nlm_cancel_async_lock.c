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
struct nlm_host {int /*<<< orphan*/  nh_lock; int /*<<< orphan*/  nh_pending; int /*<<< orphan*/  nh_sysid; int /*<<< orphan*/  nh_caller_name; } ;
struct nlm_async_lock {int /*<<< orphan*/  af_task; int /*<<< orphan*/  af_cookie; int /*<<< orphan*/  af_fl; int /*<<< orphan*/  af_vp; struct nlm_host* af_host; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_CANCEL ; 
 int /*<<< orphan*/  F_REMOTE ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  NLM_DEBUG (int,char*,struct nlm_async_lock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nlm_async_lock*,int /*<<< orphan*/ ) ; 
 int VOP_ADVLOCKASYNC (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  af_link ; 
 int /*<<< orphan*/  mtx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_free_async_lock (struct nlm_async_lock*) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_thread ; 

__attribute__((used)) static int
nlm_cancel_async_lock(struct nlm_async_lock *af)
{
	struct nlm_host *host = af->af_host;
	int error;

	mtx_assert(&host->nh_lock, MA_OWNED);

	mtx_unlock(&host->nh_lock);

	error = VOP_ADVLOCKASYNC(af->af_vp, NULL, F_CANCEL, &af->af_fl,
	    F_REMOTE, NULL, &af->af_cookie);

	if (error) {
		/*
		 * We failed to cancel - make sure our callback has
		 * completed before we continue.
		 */
		taskqueue_drain(taskqueue_thread, &af->af_task);
	}

	mtx_lock(&host->nh_lock);
	
	if (!error) {
		NLM_DEBUG(2, "NLM: async lock %p for %s (sysid %d) "
		    "cancelled\n", af, host->nh_caller_name, host->nh_sysid);

		/*
		 * Remove from the nh_pending list and free now that
		 * we are safe from the callback.
		 */
		TAILQ_REMOVE(&host->nh_pending, af, af_link);
		mtx_unlock(&host->nh_lock);
		nlm_free_async_lock(af);
		mtx_lock(&host->nh_lock);
	}

	return (error);
}