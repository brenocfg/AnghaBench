#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* uma_zone_t ;
struct malloc_type {int dummy; } ;
typedef  void* caddr_t ;
struct TYPE_5__ {TYPE_1__** kz_zone; } ;
struct TYPE_4__ {size_t uz_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 size_t KMEM_ZBASE ; 
 size_t KMEM_ZMASK ; 
 size_t KMEM_ZSHIFT ; 
 int M_EXEC ; 
 int M_WAITOK ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 size_t kmem_zmax ; 
 int* kmemsize ; 
 TYPE_3__* kmemzones ; 
 int /*<<< orphan*/ * krequests ; 
 scalar_t__ malloc_dbg (void**,size_t*,struct malloc_type*,int) ; 
 int /*<<< orphan*/  malloc_type_allocated (struct malloc_type*,size_t) ; 
 int /*<<< orphan*/  malloc_type_zone_allocated (struct malloc_type*,size_t,int) ; 
 size_t mtp_get_subzone (struct malloc_type*) ; 
 void* redzone_setup (void*,unsigned long) ; 
 size_t roundup (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  t_malloc_fail ; 
 int /*<<< orphan*/  time_uptime ; 
 void* uma_large_malloc_domain (size_t,int,int) ; 
 void* uma_zalloc_domain (TYPE_1__*,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static void *
malloc_domain(size_t size, struct malloc_type *mtp, int domain, int flags)
{
	int indx;
	caddr_t va;
	uma_zone_t zone;
#if defined(DEBUG_REDZONE)
	unsigned long osize = size;
#endif

#ifdef MALLOC_DEBUG
	va = NULL;
	if (malloc_dbg(&va, &size, mtp, flags) != 0)
		return (va);
#endif
	if (size <= kmem_zmax && (flags & M_EXEC) == 0) {
		if (size & KMEM_ZMASK)
			size = (size & ~KMEM_ZMASK) + KMEM_ZBASE;
		indx = kmemsize[size >> KMEM_ZSHIFT];
		zone = kmemzones[indx].kz_zone[mtp_get_subzone(mtp)];
#ifdef MALLOC_PROFILE
		krequests[size >> KMEM_ZSHIFT]++;
#endif
		va = uma_zalloc_domain(zone, NULL, domain, flags);
		if (va != NULL)
			size = zone->uz_size;
		malloc_type_zone_allocated(mtp, va == NULL ? 0 : size, indx);
	} else {
		size = roundup(size, PAGE_SIZE);
		zone = NULL;
		va = uma_large_malloc_domain(size, domain, flags);
		malloc_type_allocated(mtp, va == NULL ? 0 : size);
	}
	if (flags & M_WAITOK)
		KASSERT(va != NULL, ("malloc(M_WAITOK) returned NULL"));
	else if (va == NULL)
		t_malloc_fail = time_uptime;
#ifdef DEBUG_REDZONE
	if (va != NULL)
		va = redzone_setup(va, osize);
#endif
	return ((void *) va);
}