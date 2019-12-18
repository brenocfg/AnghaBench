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
struct nlm_waiting_lock {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_NLM ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct nlm_waiting_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct nlm_waiting_lock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nlm_global_lock ; 
 int /*<<< orphan*/  nlm_waiting_locks ; 
 int /*<<< orphan*/  nw_link ; 

void
nlm_deregister_wait_lock(void *handle)
{
	struct nlm_waiting_lock *nw = handle;

	mtx_lock(&nlm_global_lock);
	TAILQ_REMOVE(&nlm_waiting_locks, nw, nw_link);
	mtx_unlock(&nlm_global_lock);
	
	free(nw, M_NLM);
}