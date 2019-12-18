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
typedef  int /*<<< orphan*/  vm_page_t ;

/* Variables and functions */
 int /*<<< orphan*/  DRM_ERROR (char*) ; 
 int /*<<< orphan*/  pmap_invalidate_cache_pages (int /*<<< orphan*/ *,unsigned long) ; 

void
drm_clflush_pages(vm_page_t *pages, unsigned long num_pages)
{

#if defined(__i386__) || defined(__amd64__)
	pmap_invalidate_cache_pages(pages, num_pages);
#else
	DRM_ERROR("drm_clflush_pages not implemented on this architecture");
#endif
}