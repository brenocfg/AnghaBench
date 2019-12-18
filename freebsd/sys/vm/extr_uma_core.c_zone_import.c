#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
typedef  TYPE_2__* uma_slab_t ;
typedef  TYPE_3__* uma_keg_t ;
struct TYPE_13__ {scalar_t__ uk_free; scalar_t__ uk_reserve; } ;
struct TYPE_12__ {scalar_t__ us_freecount; TYPE_3__* us_keg; } ;
struct TYPE_11__ {int uz_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEG_UNLOCK (TYPE_3__*) ; 
 int M_NOWAIT ; 
 int M_WAITOK ; 
 int UMA_ZONE_NUMA ; 
 int howmany (int,int) ; 
 void* slab_alloc_item (TYPE_3__*,TYPE_2__*) ; 
 int vm_ndomains ; 
 TYPE_2__* zone_fetch_slab (TYPE_1__*,TYPE_3__*,int,int) ; 

__attribute__((used)) static int
zone_import(uma_zone_t zone, void **bucket, int max, int domain, int flags)
{
	uma_slab_t slab;
	uma_keg_t keg;
#ifdef NUMA
	int stripe;
#endif
	int i;

	slab = NULL;
	keg = NULL;
	/* Try to keep the buckets totally full */
	for (i = 0; i < max; ) {
		if ((slab = zone_fetch_slab(zone, keg, domain, flags)) == NULL)
			break;
		keg = slab->us_keg;
#ifdef NUMA
		stripe = howmany(max, vm_ndomains);
#endif
		while (slab->us_freecount && i < max) { 
			bucket[i++] = slab_alloc_item(keg, slab);
			if (keg->uk_free <= keg->uk_reserve)
				break;
#ifdef NUMA
			/*
			 * If the zone is striped we pick a new slab for every
			 * N allocations.  Eliminating this conditional will
			 * instead pick a new domain for each bucket rather
			 * than stripe within each bucket.  The current option
			 * produces more fragmentation and requires more cpu
			 * time but yields better distribution.
			 */
			if ((zone->uz_flags & UMA_ZONE_NUMA) == 0 &&
			    vm_ndomains > 1 && --stripe == 0)
				break;
#endif
		}
		/* Don't block if we allocated any successfully. */
		flags &= ~M_WAITOK;
		flags |= M_NOWAIT;
	}
	if (slab != NULL)
		KEG_UNLOCK(keg);

	return i;
}