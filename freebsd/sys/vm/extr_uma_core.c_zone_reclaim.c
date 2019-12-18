#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
struct TYPE_8__ {int uz_flags; int /*<<< orphan*/  uz_keg; int /*<<< orphan*/  uz_lockptr; } ;

/* Variables and functions */
 int M_NOWAIT ; 
 int /*<<< orphan*/  PVM ; 
 int UMA_ZFLAG_CACHE ; 
 int UMA_ZFLAG_RECLAIMING ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bucket_cache_reclaim (TYPE_1__*,int) ; 
 int /*<<< orphan*/  keg_drain (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wakeup (TYPE_1__*) ; 

__attribute__((used)) static void
zone_reclaim(uma_zone_t zone, int waitok, bool drain)
{

	/*
	 * Set draining to interlock with zone_dtor() so we can release our
	 * locks as we go.  Only dtor() should do a WAITOK call since it
	 * is the only call that knows the structure will still be available
	 * when it wakes up.
	 */
	ZONE_LOCK(zone);
	while (zone->uz_flags & UMA_ZFLAG_RECLAIMING) {
		if (waitok == M_NOWAIT)
			goto out;
		msleep(zone, zone->uz_lockptr, PVM, "zonedrain", 1);
	}
	zone->uz_flags |= UMA_ZFLAG_RECLAIMING;
	bucket_cache_reclaim(zone, drain);
	ZONE_UNLOCK(zone);

	/*
	 * The DRAINING flag protects us from being freed while
	 * we're running.  Normally the uma_rwlock would protect us but we
	 * must be able to release and acquire the right lock for each keg.
	 */
	if ((zone->uz_flags & UMA_ZFLAG_CACHE) == 0)
		keg_drain(zone->uz_keg);
	ZONE_LOCK(zone);
	zone->uz_flags &= ~UMA_ZFLAG_RECLAIMING;
	wakeup(zone);
out:
	ZONE_UNLOCK(zone);
}