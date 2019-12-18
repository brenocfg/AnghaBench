#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_zone_domain_t ;
typedef  TYPE_3__* uma_bucket_t ;
struct TYPE_15__ {long ub_cnt; } ;
struct TYPE_14__ {long uzd_nitems; scalar_t__ uzd_imin; scalar_t__ uzd_imax; int /*<<< orphan*/  uzd_buckets; int /*<<< orphan*/  uzd_wss; } ;
struct TYPE_13__ {scalar_t__ uz_count; scalar_t__ uz_count_min; TYPE_2__* uz_domain; } ;

/* Variables and functions */
 TYPE_3__* TAILQ_LAST (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bucket_drain (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bucket_free (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 long lmax (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ lmin (scalar_t__,long) ; 
 int /*<<< orphan*/  ub_link ; 
 int /*<<< orphan*/  uma_bucketlist ; 
 int vm_ndomains ; 

__attribute__((used)) static void
bucket_cache_reclaim(uma_zone_t zone, bool drain)
{
	uma_zone_domain_t zdom;
	uma_bucket_t bucket;
	long target, tofree;
	int i;

	for (i = 0; i < vm_ndomains; i++) {
		zdom = &zone->uz_domain[i];

		/*
		 * If we were asked to drain the zone, we are done only once
		 * this bucket cache is empty.  Otherwise, we reclaim items in
		 * excess of the zone's estimated working set size.  If the
		 * difference nitems - imin is larger than the WSS estimate,
		 * then the estimate will grow at the end of this interval and
		 * we ignore the historical average.
		 */
		target = drain ? 0 : lmax(zdom->uzd_wss, zdom->uzd_nitems -
		    zdom->uzd_imin);
		while (zdom->uzd_nitems > target) {
			bucket = TAILQ_LAST(&zdom->uzd_buckets, uma_bucketlist);
			if (bucket == NULL)
				break;
			tofree = bucket->ub_cnt;
			TAILQ_REMOVE(&zdom->uzd_buckets, bucket, ub_link);
			zdom->uzd_nitems -= tofree;

			/*
			 * Shift the bounds of the current WSS interval to avoid
			 * perturbing the estimate.
			 */
			zdom->uzd_imax -= lmin(zdom->uzd_imax, tofree);
			zdom->uzd_imin -= lmin(zdom->uzd_imin, tofree);

			ZONE_UNLOCK(zone);
			bucket_drain(zone, bucket);
			bucket_free(zone, bucket, NULL);
			ZONE_LOCK(zone);
		}
	}

	/*
	 * Shrink the zone bucket size to ensure that the per-CPU caches
	 * don't grow too large.
	 */
	if (zone->uz_count > zone->uz_count_min)
		zone->uz_count--;
}