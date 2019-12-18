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
typedef  TYPE_1__* uma_keg_t ;
struct TYPE_8__ {int uz_flags; int /*<<< orphan*/  uz_lock; int /*<<< orphan*/ * uz_lockptr; int /*<<< orphan*/  uz_fails; int /*<<< orphan*/  uz_frees; int /*<<< orphan*/  uz_allocs; struct TYPE_8__* uz_keg; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  SKIP_NONE ; 
 int UMA_ZFLAG_CACHE ; 
 int UMA_ZFLAG_INTERNAL ; 
 int UMA_ZONE_SECONDARY ; 
 int /*<<< orphan*/  ZONE_LOCK_FINI (TYPE_1__*) ; 
 int /*<<< orphan*/  cache_drain (TYPE_1__*) ; 
 int /*<<< orphan*/  counter_u64_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kegs ; 
 int /*<<< orphan*/  rw_wlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_wunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uk_link ; 
 int /*<<< orphan*/  uma_rwlock ; 
 int /*<<< orphan*/  uz_link ; 
 int /*<<< orphan*/  zone_free_item (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_reclaim (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
zone_dtor(void *arg, int size, void *udata)
{
	uma_zone_t zone;
	uma_keg_t keg;

	zone = (uma_zone_t)arg;

	if (!(zone->uz_flags & UMA_ZFLAG_INTERNAL))
		cache_drain(zone);

	rw_wlock(&uma_rwlock);
	LIST_REMOVE(zone, uz_link);
	rw_wunlock(&uma_rwlock);
	/*
	 * XXX there are some races here where
	 * the zone can be drained but zone lock
	 * released and then refilled before we
	 * remove it... we dont care for now
	 */
	zone_reclaim(zone, M_WAITOK, true);
	/*
	 * We only destroy kegs from non secondary/non cache zones.
	 */
	if ((zone->uz_flags & (UMA_ZONE_SECONDARY | UMA_ZFLAG_CACHE)) == 0) {
		keg = zone->uz_keg;
		rw_wlock(&uma_rwlock);
		LIST_REMOVE(keg, uk_link);
		rw_wunlock(&uma_rwlock);
		zone_free_item(kegs, keg, NULL, SKIP_NONE);
	}
	counter_u64_free(zone->uz_allocs);
	counter_u64_free(zone->uz_frees);
	counter_u64_free(zone->uz_fails);
	if (zone->uz_lockptr == &zone->uz_lock)
		ZONE_LOCK_FINI(zone);
}