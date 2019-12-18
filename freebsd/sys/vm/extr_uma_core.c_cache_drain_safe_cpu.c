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
typedef  TYPE_2__* uma_cache_t ;
typedef  TYPE_3__* uma_bucket_t ;
struct TYPE_15__ {scalar_t__ ub_cnt; } ;
struct TYPE_14__ {TYPE_3__* uc_crossbucket; TYPE_3__* uc_freebucket; TYPE_3__* uc_allocbucket; } ;
struct TYPE_13__ {int uz_flags; int /*<<< orphan*/ * uz_domain; TYPE_2__* uz_cpu; } ;

/* Variables and functions */
 int PCPU_GET (int) ; 
 int UMA_ZFLAG_INTERNAL ; 
 int UMA_ZONE_NUMA ; 
 int /*<<< orphan*/  ZONE_LOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  ZONE_UNLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  bucket_drain (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  bucket_free (TYPE_1__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  critical_enter () ; 
 int /*<<< orphan*/  critical_exit () ; 
 size_t curcpu ; 
 int /*<<< orphan*/  zone_put_bucket (TYPE_1__*,int /*<<< orphan*/ *,TYPE_3__*,int) ; 

__attribute__((used)) static void
cache_drain_safe_cpu(uma_zone_t zone)
{
	uma_cache_t cache;
	uma_bucket_t b1, b2, b3;
	int domain;

	if (zone->uz_flags & UMA_ZFLAG_INTERNAL)
		return;

	b1 = b2 = b3 = NULL;
	ZONE_LOCK(zone);
	critical_enter();
	if (zone->uz_flags & UMA_ZONE_NUMA)
		domain = PCPU_GET(domain);
	else
		domain = 0;
	cache = &zone->uz_cpu[curcpu];
	if (cache->uc_allocbucket) {
		if (cache->uc_allocbucket->ub_cnt != 0)
			zone_put_bucket(zone, &zone->uz_domain[domain],
			    cache->uc_allocbucket, false);
		else
			b1 = cache->uc_allocbucket;
		cache->uc_allocbucket = NULL;
	}
	if (cache->uc_freebucket) {
		if (cache->uc_freebucket->ub_cnt != 0)
			zone_put_bucket(zone, &zone->uz_domain[domain],
			    cache->uc_freebucket, false);
		else
			b2 = cache->uc_freebucket;
		cache->uc_freebucket = NULL;
	}
	b3 = cache->uc_crossbucket;
	cache->uc_crossbucket = NULL;
	critical_exit();
	ZONE_UNLOCK(zone);
	if (b1)
		bucket_free(zone, b1, NULL);
	if (b2)
		bucket_free(zone, b2, NULL);
	if (b3) {
		bucket_drain(zone, b3);
		bucket_free(zone, b3, NULL);
	}
}