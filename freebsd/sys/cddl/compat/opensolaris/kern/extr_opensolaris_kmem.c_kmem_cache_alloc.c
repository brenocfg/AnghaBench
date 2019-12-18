#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  kc_size; int /*<<< orphan*/ * kc_constructor; int /*<<< orphan*/  kc_zone; } ;
typedef  TYPE_1__ kmem_cache_t ;

/* Variables and functions */
 void* kmem_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kmem_std_constructor (void*,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 void* uma_zalloc_arg (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

void *
kmem_cache_alloc(kmem_cache_t *cache, int flags)
{
#if defined(_KERNEL) && !defined(KMEM_DEBUG)
	return (uma_zalloc_arg(cache->kc_zone, cache, flags));
#else
	void *p;

	p = kmem_alloc(cache->kc_size, flags);
	if (p != NULL && cache->kc_constructor != NULL)
		kmem_std_constructor(p, cache->kc_size, cache, flags);
	return (p);
#endif
}