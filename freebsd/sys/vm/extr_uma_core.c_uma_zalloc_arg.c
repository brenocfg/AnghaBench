#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_4__ ;
typedef  struct TYPE_38__   TYPE_3__ ;
typedef  struct TYPE_37__   TYPE_2__ ;
typedef  struct TYPE_36__   TYPE_22__ ;
typedef  struct TYPE_35__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone ;
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_zone_domain_t ;
typedef  TYPE_3__* uma_cache_t ;
typedef  TYPE_4__* uma_bucket_t ;
struct TYPE_39__ {size_t ub_cnt; int /*<<< orphan*/ ** ub_bucket; } ;
struct TYPE_38__ {TYPE_4__* uc_allocbucket; TYPE_4__* uc_freebucket; int /*<<< orphan*/  uc_allocs; } ;
struct TYPE_37__ {int uzd_imax; } ;
struct TYPE_36__ {scalar_t__ td_critnest; } ;
struct TYPE_35__ {int uz_flags; scalar_t__ (* uz_init ) (void*,int /*<<< orphan*/ ,int) ;scalar_t__ (* uz_ctor ) (void*,int /*<<< orphan*/ ,void*,int) ;scalar_t__ uz_dtor; int uz_count; int uz_count_max; scalar_t__ uz_max_items; scalar_t__ uz_items; scalar_t__ uz_sleepers; scalar_t__ uz_bkt_count; scalar_t__ uz_bkt_max; TYPE_3__* uz_cpu; int /*<<< orphan*/  uz_name; TYPE_2__* uz_domain; int /*<<< orphan*/  uz_fails; int /*<<< orphan*/  uz_size; int /*<<< orphan*/  (* uz_fini ) (void*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  CTR4 (int /*<<< orphan*/ ,char*,TYPE_22__*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int M_EXEC ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int PCPU_GET (int) ; 
 int /*<<< orphan*/  RANDOM_UMA ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int SKIP_CNT ; 
 int SKIP_DTOR ; 
 int UMA_ANYDOMAIN ; 
 int UMA_ZONE_NUMA ; 
 int UMA_ZONE_PCPU ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 scalar_t__ ZONE_TRYLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bucket_drain (TYPE_1__*,TYPE_4__*) ; 
 int /*<<< orphan*/  bucket_free (TYPE_1__*,TYPE_4__*,void*) ; 
 scalar_t__ bucketdisable ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int curcpu ; 
 TYPE_22__* curthread ; 
 void* memguard_alloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ memguard_cmp_zone (TYPE_1__*) ; 
 int /*<<< orphan*/  random_harvest_fast_uma (TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (void*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ stub2 (void*,int /*<<< orphan*/ ,void*,int) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ) ; 
 scalar_t__ stub4 (void*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ trash_ctor (void*,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ trash_dtor ; 
 int /*<<< orphan*/  uma_dbg_alloc (TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int uma_dbg_zskip (TYPE_1__*,void*) ; 
 int /*<<< orphan*/  uma_zero_item (void*,TYPE_1__*) ; 
 int /*<<< orphan*/  wakeup_one (TYPE_1__*) ; 
 TYPE_4__* zone_alloc_bucket (TYPE_1__*,void*,int,int,int) ; 
 void* zone_alloc_item_locked (TYPE_1__*,void*,int,int) ; 
 TYPE_4__* zone_fetch_bucket (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  zone_free_item (TYPE_1__*,void*,void*,int) ; 
 int /*<<< orphan*/  zone_put_bucket (TYPE_1__*,TYPE_2__*,TYPE_4__*,int) ; 

void *
uma_zalloc_arg(uma_zone_t zone, void *udata, int flags)
{
	uma_zone_domain_t zdom;
	uma_bucket_t bucket;
	uma_cache_t cache;
	void *item;
	int cpu, domain, lockfail, maxbucket;
#ifdef INVARIANTS
	bool skipdbg;
#endif

	/* Enable entropy collection for RANDOM_ENABLE_UMA kernel option */
	random_harvest_fast_uma(&zone, sizeof(zone), RANDOM_UMA);

	/* This is the fast path allocation */
	CTR4(KTR_UMA, "uma_zalloc_arg thread %x zone %s(%p) flags %d",
	    curthread, zone->uz_name, zone, flags);

	if (flags & M_WAITOK) {
		WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
		    "uma_zalloc_arg: zone \"%s\"", zone->uz_name);
	}
	KASSERT((flags & M_EXEC) == 0, ("uma_zalloc_arg: called with M_EXEC"));
	KASSERT(curthread->td_critnest == 0 || SCHEDULER_STOPPED(),
	    ("uma_zalloc_arg: called with spinlock or critical section held"));
	if (zone->uz_flags & UMA_ZONE_PCPU)
		KASSERT((flags & M_ZERO) == 0, ("allocating from a pcpu zone "
		    "with M_ZERO passed"));

#ifdef DEBUG_MEMGUARD
	if (memguard_cmp_zone(zone)) {
		item = memguard_alloc(zone->uz_size, flags);
		if (item != NULL) {
			if (zone->uz_init != NULL &&
			    zone->uz_init(item, zone->uz_size, flags) != 0)
				return (NULL);
			if (zone->uz_ctor != NULL &&
			    zone->uz_ctor(item, zone->uz_size, udata,
			    flags) != 0) {
			    	zone->uz_fini(item, zone->uz_size);
				return (NULL);
			}
			return (item);
		}
		/* This is unfortunate but should not be fatal. */
	}
#endif
	/*
	 * If possible, allocate from the per-CPU cache.  There are two
	 * requirements for safe access to the per-CPU cache: (1) the thread
	 * accessing the cache must not be preempted or yield during access,
	 * and (2) the thread must not migrate CPUs without switching which
	 * cache it accesses.  We rely on a critical section to prevent
	 * preemption and migration.  We release the critical section in
	 * order to acquire the zone mutex if we are unable to allocate from
	 * the current cache; when we re-acquire the critical section, we
	 * must detect and handle migration if it has occurred.
	 */
zalloc_restart:
	critical_enter();
	cpu = curcpu;
	cache = &zone->uz_cpu[cpu];

zalloc_start:
	bucket = cache->uc_allocbucket;
	if (bucket != NULL && bucket->ub_cnt > 0) {
		bucket->ub_cnt--;
		item = bucket->ub_bucket[bucket->ub_cnt];
#ifdef INVARIANTS
		bucket->ub_bucket[bucket->ub_cnt] = NULL;
#endif
		KASSERT(item != NULL, ("uma_zalloc: Bucket pointer mangled."));
		cache->uc_allocs++;
		critical_exit();
#ifdef INVARIANTS
		skipdbg = uma_dbg_zskip(zone, item);
#endif
		if (zone->uz_ctor != NULL &&
#ifdef INVARIANTS
		    (!skipdbg || zone->uz_ctor != trash_ctor ||
		    zone->uz_dtor != trash_dtor) &&
#endif
		    zone->uz_ctor(item, zone->uz_size, udata, flags) != 0) {
			counter_u64_add(zone->uz_fails, 1);
			zone_free_item(zone, item, udata, SKIP_DTOR | SKIP_CNT);
			return (NULL);
		}
#ifdef INVARIANTS
		if (!skipdbg)
			uma_dbg_alloc(zone, NULL, item);
#endif
		if (flags & M_ZERO)
			uma_zero_item(item, zone);
		return (item);
	}

	/*
	 * We have run out of items in our alloc bucket.
	 * See if we can switch with our free bucket.
	 */
	bucket = cache->uc_freebucket;
	if (bucket != NULL && bucket->ub_cnt > 0) {
		CTR2(KTR_UMA,
		    "uma_zalloc: zone %s(%p) swapping empty with alloc",
		    zone->uz_name, zone);
		cache->uc_freebucket = cache->uc_allocbucket;
		cache->uc_allocbucket = bucket;
		goto zalloc_start;
	}

	/*
	 * Discard any empty allocation bucket while we hold no locks.
	 */
	bucket = cache->uc_allocbucket;
	cache->uc_allocbucket = NULL;
	critical_exit();
	if (bucket != NULL)
		bucket_free(zone, bucket, udata);

	/* Short-circuit for zones without buckets and low memory. */
	if (zone->uz_count == 0 || bucketdisable) {
		ZONE_LOCK(zone);
		if (zone->uz_flags & UMA_ZONE_NUMA)
			domain = PCPU_GET(domain);
		else
			domain = UMA_ANYDOMAIN;
		goto zalloc_item;
	}

	/*
	 * Attempt to retrieve the item from the per-CPU cache has failed, so
	 * we must go back to the zone.  This requires the zone lock, so we
	 * must drop the critical section, then re-acquire it when we go back
	 * to the cache.  Since the critical section is released, we may be
	 * preempted or migrate.  As such, make sure not to maintain any
	 * thread-local state specific to the cache from prior to releasing
	 * the critical section.
	 */
	lockfail = 0;
	if (ZONE_TRYLOCK(zone) == 0) {
		/* Record contention to size the buckets. */
		ZONE_LOCK(zone);
		lockfail = 1;
	}
	critical_enter();
	cpu = curcpu;
	cache = &zone->uz_cpu[cpu];

	/* See if we lost the race to fill the cache. */
	if (cache->uc_allocbucket != NULL) {
		ZONE_UNLOCK(zone);
		goto zalloc_start;
	}

	/*
	 * Check the zone's cache of buckets.
	 */
	if (zone->uz_flags & UMA_ZONE_NUMA) {
		domain = PCPU_GET(domain);
		zdom = &zone->uz_domain[domain];
	} else {
		domain = UMA_ANYDOMAIN;
		zdom = &zone->uz_domain[0];
	}

	if ((bucket = zone_fetch_bucket(zone, zdom)) != NULL) {
		KASSERT(bucket->ub_cnt != 0,
		    ("uma_zalloc_arg: Returning an empty bucket."));
		cache->uc_allocbucket = bucket;
		ZONE_UNLOCK(zone);
		goto zalloc_start;
	}
	/* We are no longer associated with this CPU. */
	critical_exit();

	/*
	 * We bump the uz count when the cache size is insufficient to
	 * handle the working set.
	 */
	if (lockfail && zone->uz_count < zone->uz_count_max)
		zone->uz_count++;

	if (zone->uz_max_items > 0) {
		if (zone->uz_items >= zone->uz_max_items)
			goto zalloc_item;
		maxbucket = MIN(zone->uz_count,
		    zone->uz_max_items - zone->uz_items);
		zone->uz_items += maxbucket;
	} else
		maxbucket = zone->uz_count;
	ZONE_UNLOCK(zone);

	/*
	 * Now lets just fill a bucket and put it on the free list.  If that
	 * works we'll restart the allocation from the beginning and it
	 * will use the just filled bucket.
	 */
	bucket = zone_alloc_bucket(zone, udata, domain, flags, maxbucket);
	CTR3(KTR_UMA, "uma_zalloc: zone %s(%p) bucket zone returned %p",
	    zone->uz_name, zone, bucket);
	ZONE_LOCK(zone);
	if (bucket != NULL) {
		if (zone->uz_max_items > 0 && bucket->ub_cnt < maxbucket) {
			MPASS(zone->uz_items >= maxbucket - bucket->ub_cnt);
			zone->uz_items -= maxbucket - bucket->ub_cnt;
			if (zone->uz_sleepers > 0 &&
			    zone->uz_items < zone->uz_max_items)
				wakeup_one(zone);
		}
		critical_enter();
		cpu = curcpu;
		cache = &zone->uz_cpu[cpu];

		/*
		 * See if we lost the race or were migrated.  Cache the
		 * initialized bucket to make this less likely or claim
		 * the memory directly.
		 */
		if (cache->uc_allocbucket == NULL &&
		    ((zone->uz_flags & UMA_ZONE_NUMA) == 0 ||
		    domain == PCPU_GET(domain))) {
			cache->uc_allocbucket = bucket;
			zdom->uzd_imax += bucket->ub_cnt;
		} else if (zone->uz_bkt_count >= zone->uz_bkt_max) {
			critical_exit();
			ZONE_UNLOCK(zone);
			bucket_drain(zone, bucket);
			bucket_free(zone, bucket, udata);
			goto zalloc_restart;
		} else
			zone_put_bucket(zone, zdom, bucket, false);
		ZONE_UNLOCK(zone);
		goto zalloc_start;
	} else if (zone->uz_max_items > 0) {
		zone->uz_items -= maxbucket;
		if (zone->uz_sleepers > 0 &&
		    zone->uz_items + 1 < zone->uz_max_items)
			wakeup_one(zone);
	}

	/*
	 * We may not be able to get a bucket so return an actual item.
	 */
zalloc_item:
	item = zone_alloc_item_locked(zone, udata, domain, flags);

	return (item);
}