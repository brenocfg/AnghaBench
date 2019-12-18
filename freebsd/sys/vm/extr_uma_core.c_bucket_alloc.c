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
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_bucket_t ;
struct uma_bucket_zone {scalar_t__ ubz_entries; TYPE_1__* ubz_zone; } ;
struct TYPE_8__ {int ub_entries; scalar_t__ ub_cnt; int /*<<< orphan*/  ub_bucket; } ;
struct TYPE_7__ {uintptr_t uz_flags; int /*<<< orphan*/  uz_count; } ;

/* Variables and functions */
 int M_NOVM ; 
 uintptr_t UMA_ZFLAG_BUCKET ; 
 uintptr_t UMA_ZFLAG_CACHEONLY ; 
 struct uma_bucket_zone* bucket_zone_lookup (int /*<<< orphan*/ ) ; 
 scalar_t__ bucketdisable ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ ,int) ; 
 TYPE_2__* uma_zalloc_arg (TYPE_1__*,void*,int) ; 

__attribute__((used)) static uma_bucket_t
bucket_alloc(uma_zone_t zone, void *udata, int flags)
{
	struct uma_bucket_zone *ubz;
	uma_bucket_t bucket;

	/*
	 * This is to stop us from allocating per cpu buckets while we're
	 * running out of vm.boot_pages.  Otherwise, we would exhaust the
	 * boot pages.  This also prevents us from allocating buckets in
	 * low memory situations.
	 */
	if (bucketdisable)
		return (NULL);
	/*
	 * To limit bucket recursion we store the original zone flags
	 * in a cookie passed via zalloc_arg/zfree_arg.  This allows the
	 * NOVM flag to persist even through deep recursions.  We also
	 * store ZFLAG_BUCKET once we have recursed attempting to allocate
	 * a bucket for a bucket zone so we do not allow infinite bucket
	 * recursion.  This cookie will even persist to frees of unused
	 * buckets via the allocation path or bucket allocations in the
	 * free path.
	 */
	if ((zone->uz_flags & UMA_ZFLAG_BUCKET) == 0)
		udata = (void *)(uintptr_t)zone->uz_flags;
	else {
		if ((uintptr_t)udata & UMA_ZFLAG_BUCKET)
			return (NULL);
		udata = (void *)((uintptr_t)udata | UMA_ZFLAG_BUCKET);
	}
	if ((uintptr_t)udata & UMA_ZFLAG_CACHEONLY)
		flags |= M_NOVM;
	ubz = bucket_zone_lookup(zone->uz_count);
	if (ubz->ubz_zone == zone && (ubz + 1)->ubz_entries != 0)
		ubz++;
	bucket = uma_zalloc_arg(ubz->ubz_zone, udata, flags);
	if (bucket) {
#ifdef INVARIANTS
		bzero(bucket->ub_bucket, sizeof(void *) * ubz->ubz_entries);
#endif
		bucket->ub_cnt = 0;
		bucket->ub_entries = ubz->ubz_entries;
	}

	return (bucket);
}