#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
struct sysctl_oid_list {int dummy; } ;
struct TYPE_7__ {int sg_minthreads; int sg_maxthreads; int /*<<< orphan*/  sg_idlethreads; int /*<<< orphan*/  sg_active; int /*<<< orphan*/  sg_xlist; int /*<<< orphan*/  sg_state; TYPE_1__* sg_pool; int /*<<< orphan*/  sg_lock; } ;
struct TYPE_6__ {char const* sp_name; int sp_minthreads; int sp_maxthreads; int sp_groupcount; int sp_space_high; int sp_space_low; int sp_space_used; int sp_space_used_highest; int sp_space_throttled; int sp_space_throttle_count; int /*<<< orphan*/  sp_sysctl; TYPE_2__* sp_groups; int /*<<< orphan*/  sp_lcallouts; int /*<<< orphan*/  sp_callouts; int /*<<< orphan*/ * sp_proc; int /*<<< orphan*/  sp_state; int /*<<< orphan*/  sp_lock; } ;
typedef  TYPE_1__ SVCPOOL ;
typedef  TYPE_2__ SVCGROUP ;

/* Variables and functions */
 int CTLFLAG_RD ; 
 int CTLFLAG_RW ; 
 int CTLTYPE_INT ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int MCLBYTES ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_RPC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  OID_AUTO ; 
 int /*<<< orphan*/  SVCPOOL_ACTIVE ; 
 int /*<<< orphan*/  SVCPOOL_INIT ; 
 int SVC_MAXGROUPS ; 
 int /*<<< orphan*/  SYSCTL_ADD_INT (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_PROC (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYSCTL_ADD_ULONG (int /*<<< orphan*/ *,struct sysctl_oid_list*,int /*<<< orphan*/ ,char*,int,int*,char*) ; 
 int /*<<< orphan*/  TAILQ_INIT (int /*<<< orphan*/ *) ; 
 TYPE_1__* malloc (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ nmbclusters ; 
 int /*<<< orphan*/  svcpool_maxthread_sysctl ; 
 int /*<<< orphan*/  svcpool_minthread_sysctl ; 
 int /*<<< orphan*/  svcpool_threads_sysctl ; 
 int /*<<< orphan*/  sysctl_ctx_init (int /*<<< orphan*/ *) ; 

SVCPOOL*
svcpool_create(const char *name, struct sysctl_oid_list *sysctl_base)
{
	SVCPOOL *pool;
	SVCGROUP *grp;
	int g;

	pool = malloc(sizeof(SVCPOOL), M_RPC, M_WAITOK|M_ZERO);
	
	mtx_init(&pool->sp_lock, "sp_lock", NULL, MTX_DEF);
	pool->sp_name = name;
	pool->sp_state = SVCPOOL_INIT;
	pool->sp_proc = NULL;
	TAILQ_INIT(&pool->sp_callouts);
	TAILQ_INIT(&pool->sp_lcallouts);
	pool->sp_minthreads = 1;
	pool->sp_maxthreads = 1;
	pool->sp_groupcount = 1;
	for (g = 0; g < SVC_MAXGROUPS; g++) {
		grp = &pool->sp_groups[g];
		mtx_init(&grp->sg_lock, "sg_lock", NULL, MTX_DEF);
		grp->sg_pool = pool;
		grp->sg_state = SVCPOOL_ACTIVE;
		TAILQ_INIT(&grp->sg_xlist);
		TAILQ_INIT(&grp->sg_active);
		LIST_INIT(&grp->sg_idlethreads);
		grp->sg_minthreads = 1;
		grp->sg_maxthreads = 1;
	}

	/*
	 * Don't use more than a quarter of mbuf clusters.  Nota bene:
	 * nmbclusters is an int, but nmbclusters*MCLBYTES may overflow
	 * on LP64 architectures, so cast to u_long to avoid undefined
	 * behavior.  (ILP32 architectures cannot have nmbclusters
	 * large enough to overflow for other reasons.)
	 */
	pool->sp_space_high = (u_long)nmbclusters * MCLBYTES / 4;
	pool->sp_space_low = (pool->sp_space_high / 3) * 2;

	sysctl_ctx_init(&pool->sp_sysctl);
	if (sysctl_base) {
		SYSCTL_ADD_PROC(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "minthreads", CTLTYPE_INT | CTLFLAG_RW,
		    pool, 0, svcpool_minthread_sysctl, "I",
		    "Minimal number of threads");
		SYSCTL_ADD_PROC(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "maxthreads", CTLTYPE_INT | CTLFLAG_RW,
		    pool, 0, svcpool_maxthread_sysctl, "I",
		    "Maximal number of threads");
		SYSCTL_ADD_PROC(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "threads", CTLTYPE_INT | CTLFLAG_RD,
		    pool, 0, svcpool_threads_sysctl, "I",
		    "Current number of threads");
		SYSCTL_ADD_INT(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "groups", CTLFLAG_RD, &pool->sp_groupcount, 0,
		    "Number of thread groups");

		SYSCTL_ADD_ULONG(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "request_space_used", CTLFLAG_RD,
		    &pool->sp_space_used,
		    "Space in parsed but not handled requests.");

		SYSCTL_ADD_ULONG(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "request_space_used_highest", CTLFLAG_RD,
		    &pool->sp_space_used_highest,
		    "Highest space used since reboot.");

		SYSCTL_ADD_ULONG(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "request_space_high", CTLFLAG_RW,
		    &pool->sp_space_high,
		    "Maximum space in parsed but not handled requests.");

		SYSCTL_ADD_ULONG(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "request_space_low", CTLFLAG_RW,
		    &pool->sp_space_low,
		    "Low water mark for request space.");

		SYSCTL_ADD_INT(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "request_space_throttled", CTLFLAG_RD,
		    &pool->sp_space_throttled, 0,
		    "Whether nfs requests are currently throttled");

		SYSCTL_ADD_INT(&pool->sp_sysctl, sysctl_base, OID_AUTO,
		    "request_space_throttle_count", CTLFLAG_RD,
		    &pool->sp_space_throttle_count, 0,
		    "Count of times throttling based on request space has occurred");
	}

	return pool;
}