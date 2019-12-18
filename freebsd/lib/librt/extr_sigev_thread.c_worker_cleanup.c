#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sigev_node {int sn_flags; TYPE_1__* sn_tn; } ;
struct TYPE_2__ {int /*<<< orphan*/  tn_cv; int /*<<< orphan*/ * tn_cur; } ;

/* Variables and functions */
 int SNF_REMOVED ; 
 int SNF_SYNC ; 
 int SNF_WORKING ; 
 int /*<<< orphan*/  __sigev_free (struct sigev_node*) ; 
 int /*<<< orphan*/  __sigev_list_lock () ; 
 int /*<<< orphan*/  __sigev_list_unlock () ; 
 int /*<<< orphan*/  _pthread_cond_broadcast (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
worker_cleanup(void *arg)
{
	struct sigev_node *sn = arg;

	__sigev_list_lock();
	if (sn->sn_flags & SNF_SYNC) {
		sn->sn_tn->tn_cur = NULL;
		_pthread_cond_broadcast(&sn->sn_tn->tn_cv);
	}
	if (sn->sn_flags & SNF_REMOVED)
		__sigev_free(sn);
	else
		sn->sn_flags &= ~SNF_WORKING;
	__sigev_list_unlock();
}