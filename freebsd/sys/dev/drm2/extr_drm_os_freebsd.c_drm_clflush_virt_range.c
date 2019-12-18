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
typedef  scalar_t__ vm_offset_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  pmap_force_invalidate_cache_range (scalar_t__,scalar_t__) ; 

void
drm_clflush_virt_range(char *addr, unsigned long length)
{

#if defined(__i386__) || defined(__amd64__)
	pmap_force_invalidate_cache_range((vm_offset_t)addr,
	    (vm_offset_t)addr + length);
#else
	DRM_ERROR("drm_clflush_virt_range not implemented on this architecture");
#endif
}