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
 scalar_t__ PAGE_SIZE ; 
 void* __flush_cache_all ; 
 void* __flush_icache_user_range ; 
 int /*<<< orphan*/  __flush_kernel_vmap_range ; 
 void* __local_flush_icache_user_range ; 
 int /*<<< orphan*/  board_cache_error_setup ; 
 int /*<<< orphan*/  build_clear_page () ; 
 int /*<<< orphan*/  build_copy_page () ; 
 void* flush_cache_all ; 
 int /*<<< orphan*/  flush_cache_mm ; 
 int /*<<< orphan*/  flush_cache_page ; 
 int /*<<< orphan*/  flush_cache_range ; 
 int /*<<< orphan*/  flush_data_cache_page ; 
 void* flush_icache_all ; 
 void* flush_icache_range ; 
 void* local_flush_icache_range ; 
 void* local_octeon_flush_icache_range ; 
 int /*<<< orphan*/  octeon_cache_error_setup ; 
 int /*<<< orphan*/  octeon_flush_cache_mm ; 
 int /*<<< orphan*/  octeon_flush_cache_page ; 
 int /*<<< orphan*/  octeon_flush_cache_range ; 
 int /*<<< orphan*/  octeon_flush_data_cache_page ; 
 void* octeon_flush_icache_all ; 
 void* octeon_flush_icache_range ; 
 int /*<<< orphan*/  octeon_flush_kernel_vmap_range ; 
 int /*<<< orphan*/  probe_octeon () ; 
 scalar_t__ shm_align_mask ; 

void octeon_cache_init(void)
{
	probe_octeon();

	shm_align_mask = PAGE_SIZE - 1;

	flush_cache_all			= octeon_flush_icache_all;
	__flush_cache_all		= octeon_flush_icache_all;
	flush_cache_mm			= octeon_flush_cache_mm;
	flush_cache_page		= octeon_flush_cache_page;
	flush_cache_range		= octeon_flush_cache_range;
	flush_icache_all		= octeon_flush_icache_all;
	flush_data_cache_page		= octeon_flush_data_cache_page;
	flush_icache_range		= octeon_flush_icache_range;
	local_flush_icache_range	= local_octeon_flush_icache_range;
	__flush_icache_user_range	= octeon_flush_icache_range;
	__local_flush_icache_user_range	= local_octeon_flush_icache_range;

	__flush_kernel_vmap_range	= octeon_flush_kernel_vmap_range;

	build_clear_page();
	build_copy_page();

	board_cache_error_setup = octeon_cache_error_setup;
}