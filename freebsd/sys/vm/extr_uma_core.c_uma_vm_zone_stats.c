#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_zone_domain_t ;
typedef  TYPE_3__* uma_cache_t ;
typedef  TYPE_4__* uma_bucket_t ;
struct uma_type_header {int /*<<< orphan*/  uth_xdomain; int /*<<< orphan*/  uth_sleeps; void* uth_fails; void* uth_frees; void* uth_allocs; int /*<<< orphan*/  uth_zone_free; } ;
struct uma_percpu_stat {int /*<<< orphan*/  ups_frees; int /*<<< orphan*/  ups_allocs; int /*<<< orphan*/  ups_cache_free; } ;
struct sbuf {int dummy; } ;
struct TYPE_9__ {scalar_t__ ub_cnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  uc_frees; int /*<<< orphan*/  uc_allocs; int /*<<< orphan*/  uc_crossbucket; int /*<<< orphan*/  uc_freebucket; int /*<<< orphan*/  uc_allocbucket; } ;
struct TYPE_7__ {scalar_t__ uzd_nitems; } ;
struct TYPE_6__ {TYPE_3__* uz_cpu; int /*<<< orphan*/  uz_xdomain; int /*<<< orphan*/  uz_sleeps; int /*<<< orphan*/  uz_fails; int /*<<< orphan*/  uz_frees; int /*<<< orphan*/  uz_allocs; TYPE_2__* uz_domain; } ;

/* Variables and functions */
 scalar_t__ CPU_ABSENT (int) ; 
 scalar_t__ atomic_load_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bzero (struct uma_percpu_stat*,int) ; 
 void* counter_u64_fetch (int /*<<< orphan*/ ) ; 
 int mp_maxid ; 
 int vm_ndomains ; 

__attribute__((used)) static void
uma_vm_zone_stats(struct uma_type_header *uth, uma_zone_t z, struct sbuf *sbuf,
    struct uma_percpu_stat *ups, bool internal)
{
	uma_zone_domain_t zdom;
	uma_bucket_t bucket;
	uma_cache_t cache;
	int i;


	for (i = 0; i < vm_ndomains; i++) {
		zdom = &z->uz_domain[i];
		uth->uth_zone_free += zdom->uzd_nitems;
	}
	uth->uth_allocs = counter_u64_fetch(z->uz_allocs);
	uth->uth_frees = counter_u64_fetch(z->uz_frees);
	uth->uth_fails = counter_u64_fetch(z->uz_fails);
	uth->uth_sleeps = z->uz_sleeps;
	uth->uth_xdomain = z->uz_xdomain;

	/*
	 * While it is not normally safe to access the cache bucket pointers
	 * while not on the CPU that owns the cache, we only allow the pointers
	 * to be exchanged without the zone lock held, not invalidated, so
	 * accept the possible race associated with bucket exchange during
	 * monitoring.  Use atomic_load_ptr() to ensure that the bucket pointers
	 * are loaded only once.
	 */
	for (i = 0; i < mp_maxid + 1; i++) {
		bzero(&ups[i], sizeof(*ups));
		if (internal || CPU_ABSENT(i))
			continue;
		cache = &z->uz_cpu[i];
		bucket = (uma_bucket_t)atomic_load_ptr(&cache->uc_allocbucket);
		if (bucket != NULL)
			ups[i].ups_cache_free += bucket->ub_cnt;
		bucket = (uma_bucket_t)atomic_load_ptr(&cache->uc_freebucket);
		if (bucket != NULL)
			ups[i].ups_cache_free += bucket->ub_cnt;
		bucket = (uma_bucket_t)atomic_load_ptr(&cache->uc_crossbucket);
		if (bucket != NULL)
			ups[i].ups_cache_free += bucket->ub_cnt;
		ups[i].ups_allocs = cache->uc_allocs;
		ups[i].ups_frees = cache->uc_frees;
	}
}