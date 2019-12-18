#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zone ;
typedef  int /*<<< orphan*/  vm_offset_t ;
typedef  TYPE_1__* uma_zone_t ;
typedef  int /*<<< orphan*/ * uma_zone_domain_t ;
typedef  TYPE_2__* uma_cache_t ;
typedef  TYPE_3__* uma_bucket_t ;
struct TYPE_27__ {size_t ub_cnt; size_t ub_entries; int /*<<< orphan*/ ** ub_bucket; } ;
struct TYPE_26__ {TYPE_3__* uc_freebucket; TYPE_3__* uc_crossbucket; int /*<<< orphan*/  uc_frees; TYPE_3__* uc_allocbucket; } ;
struct TYPE_25__ {int uz_flags; scalar_t__ uz_ctor; scalar_t__ uz_sleepers; scalar_t__ uz_count; size_t uz_xdomain; scalar_t__ uz_bkt_count; scalar_t__ uz_bkt_max; scalar_t__ uz_count_max; TYPE_2__* uz_cpu; int /*<<< orphan*/  uz_name; int /*<<< orphan*/ * uz_domain; int /*<<< orphan*/  uz_size; int /*<<< orphan*/  (* uz_dtor ) (void*,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* uz_fini ) (void*,int /*<<< orphan*/ ) ;} ;
struct TYPE_24__ {scalar_t__ td_critnest; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTR2 (int /*<<< orphan*/ ,char*,TYPE_11__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTR3 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  KTR_UMA ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int PCPU_GET (int) ; 
 int /*<<< orphan*/  RANDOM_UMA ; 
 scalar_t__ SCHEDULER_STOPPED () ; 
 int /*<<< orphan*/  SKIP_DTOR ; 
 int UMA_ZONE_MALLOC ; 
 int UMA_ZONE_NUMA ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 scalar_t__ ZONE_TRYLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 int _vm_phys_domain (int /*<<< orphan*/ ) ; 
 TYPE_3__* bucket_alloc (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bucket_drain (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bucket_free (TYPE_1__*,TYPE_3__*,void*) ; 
 scalar_t__ bucketdisable ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 int curcpu ; 
 TYPE_11__* curthread ; 
 scalar_t__ is_memguard_addr (void*) ; 
 int /*<<< orphan*/  memguard_free (void*) ; 
 int /*<<< orphan*/  pmap_kextract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_harvest_fast_uma (TYPE_1__**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stub2 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (void*,int /*<<< orphan*/ ,void*) ; 
 scalar_t__ trash_ctor ; 
 int /*<<< orphan*/  trash_dtor (void*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  uma_dbg_free (TYPE_1__*,void*,void*) ; 
 int uma_dbg_zskip (TYPE_1__*,void*) ; 
 int vm_ndomains ; 
 int /*<<< orphan*/  zone_free_item (TYPE_1__*,void*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zone_put_bucket (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 

void
uma_zfree_arg(uma_zone_t zone, void *item, void *udata)
{
	uma_cache_t cache;
	uma_bucket_t bucket;
	uma_zone_domain_t zdom;
	int cpu, domain;
#ifdef UMA_XDOMAIN
	int itemdomain;
#endif
	bool lockfail;
#ifdef INVARIANTS
	bool skipdbg;
#endif

	/* Enable entropy collection for RANDOM_ENABLE_UMA kernel option */
	random_harvest_fast_uma(&zone, sizeof(zone), RANDOM_UMA);

	CTR2(KTR_UMA, "uma_zfree_arg thread %x zone %s", curthread,
	    zone->uz_name);

	KASSERT(curthread->td_critnest == 0 || SCHEDULER_STOPPED(),
	    ("uma_zfree_arg: called with spinlock or critical section held"));

        /* uma_zfree(..., NULL) does nothing, to match free(9). */
        if (item == NULL)
                return;
#ifdef DEBUG_MEMGUARD
	if (is_memguard_addr(item)) {
		if (zone->uz_dtor != NULL)
			zone->uz_dtor(item, zone->uz_size, udata);
		if (zone->uz_fini != NULL)
			zone->uz_fini(item, zone->uz_size);
		memguard_free(item);
		return;
	}
#endif
#ifdef INVARIANTS
	skipdbg = uma_dbg_zskip(zone, item);
	if (skipdbg == false) {
		if (zone->uz_flags & UMA_ZONE_MALLOC)
			uma_dbg_free(zone, udata, item);
		else
			uma_dbg_free(zone, NULL, item);
	}
	if (zone->uz_dtor != NULL && (!skipdbg ||
	    zone->uz_dtor != trash_dtor || zone->uz_ctor != trash_ctor))
#else
	if (zone->uz_dtor != NULL)
#endif
		zone->uz_dtor(item, zone->uz_size, udata);

	/*
	 * The race here is acceptable.  If we miss it we'll just have to wait
	 * a little longer for the limits to be reset.
	 */
	if (zone->uz_sleepers > 0)
		goto zfree_item;

#ifdef UMA_XDOMAIN
	if ((zone->uz_flags & UMA_ZONE_NUMA) != 0)
		itemdomain = _vm_phys_domain(pmap_kextract((vm_offset_t)item));
#endif

	/*
	 * If possible, free to the per-CPU cache.  There are two
	 * requirements for safe access to the per-CPU cache: (1) the thread
	 * accessing the cache must not be preempted or yield during access,
	 * and (2) the thread must not migrate CPUs without switching which
	 * cache it accesses.  We rely on a critical section to prevent
	 * preemption and migration.  We release the critical section in
	 * order to acquire the zone mutex if we are unable to free to the
	 * current cache; when we re-acquire the critical section, we must
	 * detect and handle migration if it has occurred.
	 */
zfree_restart:
	critical_enter();
	cpu = curcpu;
	cache = &zone->uz_cpu[cpu];

zfree_start:
	domain = PCPU_GET(domain);
#ifdef UMA_XDOMAIN
	if ((zone->uz_flags & UMA_ZONE_NUMA) == 0)
		itemdomain = domain;
#endif
	/*
	 * Try to free into the allocbucket first to give LIFO ordering
	 * for cache-hot datastructures.  Spill over into the freebucket
	 * if necessary.  Alloc will swap them if one runs dry.
	 */
#ifdef UMA_XDOMAIN
	if (domain != itemdomain) {
		bucket = cache->uc_crossbucket;
	} else
#endif
	{
		bucket = cache->uc_allocbucket;
		if (bucket == NULL || bucket->ub_cnt >= bucket->ub_entries)
			bucket = cache->uc_freebucket;
	}
	if (bucket != NULL && bucket->ub_cnt < bucket->ub_entries) {
		KASSERT(bucket->ub_bucket[bucket->ub_cnt] == NULL,
		    ("uma_zfree: Freeing to non free bucket index."));
		bucket->ub_bucket[bucket->ub_cnt] = item;
		bucket->ub_cnt++;
		cache->uc_frees++;
		critical_exit();
		return;
	}

	/*
	 * We must go back the zone, which requires acquiring the zone lock,
	 * which in turn means we must release and re-acquire the critical
	 * section.  Since the critical section is released, we may be
	 * preempted or migrate.  As such, make sure not to maintain any
	 * thread-local state specific to the cache from prior to releasing
	 * the critical section.
	 */
	critical_exit();
	if (zone->uz_count == 0 || bucketdisable)
		goto zfree_item;

	lockfail = false;
	if (ZONE_TRYLOCK(zone) == 0) {
		/* Record contention to size the buckets. */
		ZONE_LOCK(zone);
		lockfail = true;
	}
	critical_enter();
	cpu = curcpu;
	domain = PCPU_GET(domain);
	cache = &zone->uz_cpu[cpu];

#ifdef UMA_XDOMAIN
	if (domain != itemdomain)
		bucket = cache->uc_crossbucket;
	else
#endif
		bucket = cache->uc_freebucket;
	if (bucket != NULL && bucket->ub_cnt < bucket->ub_entries) {
		ZONE_UNLOCK(zone);
		goto zfree_start;
	}
#ifdef UMA_XDOMAIN
	if (domain != itemdomain)
		cache->uc_crossbucket = NULL;
	else
#endif
		cache->uc_freebucket = NULL;
	/* We are no longer associated with this CPU. */
	critical_exit();

#ifdef UMA_XDOMAIN
	if (domain != itemdomain) {
		if (bucket != NULL) {
			zone->uz_xdomain += bucket->ub_cnt;
			if (vm_ndomains > 2 ||
			    zone->uz_bkt_count >= zone->uz_bkt_max) {
				ZONE_UNLOCK(zone);
				bucket_drain(zone, bucket);
				bucket_free(zone, bucket, udata);
			} else {
				zdom = &zone->uz_domain[itemdomain];
				zone_put_bucket(zone, zdom, bucket, true);
				ZONE_UNLOCK(zone);
			}
		} else
			ZONE_UNLOCK(zone);
		bucket = bucket_alloc(zone, udata, M_NOWAIT);
		if (bucket == NULL)
			goto zfree_item;
		critical_enter();
		cpu = curcpu;
		cache = &zone->uz_cpu[cpu];
		if (cache->uc_crossbucket == NULL) {
			cache->uc_crossbucket = bucket;
			goto zfree_start;
		}
		critical_exit();
		bucket_free(zone, bucket, udata);
		goto zfree_restart;
	}
#endif

	if ((zone->uz_flags & UMA_ZONE_NUMA) != 0) {
		zdom = &zone->uz_domain[domain];
	} else {
		domain = 0;
		zdom = &zone->uz_domain[0];
	}

	/* Can we throw this on the zone full list? */
	if (bucket != NULL) {
		CTR3(KTR_UMA,
		    "uma_zfree: zone %s(%p) putting bucket %p on free list",
		    zone->uz_name, zone, bucket);
		/* ub_cnt is pointing to the last free item */
		KASSERT(bucket->ub_cnt == bucket->ub_entries,
		    ("uma_zfree: Attempting to insert not full bucket onto the full list.\n"));
		if (zone->uz_bkt_count >= zone->uz_bkt_max) {
			ZONE_UNLOCK(zone);
			bucket_drain(zone, bucket);
			bucket_free(zone, bucket, udata);
			goto zfree_restart;
		} else
			zone_put_bucket(zone, zdom, bucket, true);
	}

	/*
	 * We bump the uz count when the cache size is insufficient to
	 * handle the working set.
	 */
	if (lockfail && zone->uz_count < zone->uz_count_max)
		zone->uz_count++;
	ZONE_UNLOCK(zone);

	bucket = bucket_alloc(zone, udata, M_NOWAIT);
	CTR3(KTR_UMA, "uma_zfree: zone %s(%p) allocated bucket %p",
	    zone->uz_name, zone, bucket);
	if (bucket) {
		critical_enter();
		cpu = curcpu;
		cache = &zone->uz_cpu[cpu];
		if (cache->uc_freebucket == NULL &&
		    ((zone->uz_flags & UMA_ZONE_NUMA) == 0 ||
		    domain == PCPU_GET(domain))) {
			cache->uc_freebucket = bucket;
			goto zfree_start;
		}
		/*
		 * We lost the race, start over.  We have to drop our
		 * critical section to free the bucket.
		 */
		critical_exit();
		bucket_free(zone, bucket, udata);
		goto zfree_restart;
	}

	/*
	 * If nothing else caught this, we'll just do an internal free.
	 */
zfree_item:
	zone_free_item(zone, item, udata, SKIP_DTOR);
}