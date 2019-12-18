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
struct TYPE_7__ {int dtp_refcnt; scalar_t__ dtp_cacheid; TYPE_2__* dtp_difo; } ;
typedef  TYPE_1__ dtrace_predicate_t ;
struct TYPE_8__ {scalar_t__ dtdo_refcnt; } ;
typedef  TYPE_2__ dtrace_difo_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ DTRACE_CACHEIDNONE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dtrace_difo_cacheable (TYPE_2__*) ; 
 int /*<<< orphan*/  dtrace_lock ; 
 scalar_t__ dtrace_predcache_id ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dtrace_predicate_t *
dtrace_predicate_create(dtrace_difo_t *dp)
{
	dtrace_predicate_t *pred;

	ASSERT(MUTEX_HELD(&dtrace_lock));
	ASSERT(dp->dtdo_refcnt != 0);

	pred = kmem_zalloc(sizeof (dtrace_predicate_t), KM_SLEEP);
	pred->dtp_difo = dp;
	pred->dtp_refcnt = 1;

	if (!dtrace_difo_cacheable(dp))
		return (pred);

	if (dtrace_predcache_id == DTRACE_CACHEIDNONE) {
		/*
		 * This is only theoretically possible -- we have had 2^32
		 * cacheable predicates on this machine.  We cannot allow any
		 * more predicates to become cacheable:  as unlikely as it is,
		 * there may be a thread caching a (now stale) predicate cache
		 * ID. (N.B.: the temptation is being successfully resisted to
		 * have this cmn_err() "Holy shit -- we executed this code!")
		 */
		return (pred);
	}

	pred->dtp_cacheid = dtrace_predcache_id++;

	return (pred);
}