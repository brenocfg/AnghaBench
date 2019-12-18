#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  __clean_dcache_area_pop (void*,size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

void memcpy_flushcache(void *dst, const void *src, size_t cnt)
{
	/*
	 * We assume this should not be called with @dst pointing to
	 * non-cacheable memory, such that we don't need an explicit
	 * barrier to order the cache maintenance against the memcpy.
	 */
	memcpy(dst, src, cnt);
	__clean_dcache_area_pop(dst, cnt);
}