#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_name; } ;
struct proc {int dummy; } ;
struct TYPE_8__ {int sg_minthreads; scalar_t__ sg_threadcount; int /*<<< orphan*/  sg_lock; int /*<<< orphan*/  sg_lastcreatetime; void* sg_maxthreads; } ;
struct TYPE_7__ {char* sp_name; int sp_groupcount; int sp_maxthreads; int sp_minthreads; TYPE_2__* sp_groups; struct proc* sp_proc; int /*<<< orphan*/  sp_state; } ;
typedef  TYPE_1__ SVCPOOL ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 int /*<<< orphan*/  SVCPOOL_ACTIVE ; 
 int SVC_MAXGROUPS ; 
 int /*<<< orphan*/  TRUE ; 
 struct proc* curproc ; 
 struct thread* curthread ; 
 void* max (int,int) ; 
 int min (int,int) ; 
 int mp_ncpus ; 
 int /*<<< orphan*/  msleep (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*) ; 
 int /*<<< orphan*/  svc_new_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  svc_run_internal (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 

void
svc_run(SVCPOOL *pool)
{
	int g, i;
	struct proc *p;
	struct thread *td;
	SVCGROUP *grp;

	p = curproc;
	td = curthread;
	snprintf(td->td_name, sizeof(td->td_name),
	    "%s: master", pool->sp_name);
	pool->sp_state = SVCPOOL_ACTIVE;
	pool->sp_proc = p;

	/* Choose group count based on number of threads and CPUs. */
	pool->sp_groupcount = max(1, min(SVC_MAXGROUPS,
	    min(pool->sp_maxthreads / 2, mp_ncpus) / 6));
	for (g = 0; g < pool->sp_groupcount; g++) {
		grp = &pool->sp_groups[g];
		grp->sg_minthreads = max(1,
		    pool->sp_minthreads / pool->sp_groupcount);
		grp->sg_maxthreads = max(1,
		    pool->sp_maxthreads / pool->sp_groupcount);
		grp->sg_lastcreatetime = time_uptime;
	}

	/* Starting threads */
	pool->sp_groups[0].sg_threadcount++;
	for (g = 0; g < pool->sp_groupcount; g++) {
		grp = &pool->sp_groups[g];
		for (i = ((g == 0) ? 1 : 0); i < grp->sg_minthreads; i++)
			svc_new_thread(grp);
	}
	svc_run_internal(&pool->sp_groups[0], TRUE);

	/* Waiting for threads to stop. */
	for (g = 0; g < pool->sp_groupcount; g++) {
		grp = &pool->sp_groups[g];
		mtx_lock(&grp->sg_lock);
		while (grp->sg_threadcount > 0)
			msleep(grp, &grp->sg_lock, 0, "svcexit", 0);
		mtx_unlock(&grp->sg_lock);
	}
}