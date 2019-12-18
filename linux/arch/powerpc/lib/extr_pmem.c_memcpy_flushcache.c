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
 int /*<<< orphan*/  flush_dcache_range (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  memcpy (void*,void const*,size_t) ; 

void *memcpy_flushcache(void *dest, const void *src, size_t size)
{
	unsigned long start = (unsigned long) dest;

	memcpy(dest, src, size);
	flush_dcache_range(start, start + size);

	return dest;
}