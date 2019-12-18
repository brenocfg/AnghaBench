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
 int PAGE_SIZE ; 
 int UMA_ZONE_MINBUCKET ; 
 int UMA_ZONE_NUMA ; 
 int /*<<< orphan*/  kstack_cache ; 
 int /*<<< orphan*/  kstack_cache_size ; 
 int /*<<< orphan*/  kstack_import ; 
 int kstack_pages ; 
 int /*<<< orphan*/  kstack_release ; 
 int /*<<< orphan*/  uma_zcache_create (char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uma_zone_set_maxcache (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
kstack_cache_init(void *null)
{
	kstack_cache = uma_zcache_create("kstack_cache",
	    kstack_pages * PAGE_SIZE, NULL, NULL, NULL, NULL,
	    kstack_import, kstack_release, NULL,
	    UMA_ZONE_NUMA|UMA_ZONE_MINBUCKET);
	uma_zone_set_maxcache(kstack_cache, kstack_cache_size);
}