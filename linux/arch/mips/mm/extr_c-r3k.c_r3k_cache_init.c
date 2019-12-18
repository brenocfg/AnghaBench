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
 int /*<<< orphan*/  __flush_cache_all ; 
 void* __flush_icache_user_range ; 
 int /*<<< orphan*/  __flush_kernel_vmap_range ; 
 void* __local_flush_icache_user_range ; 
 void* _dma_cache_inv ; 
 void* _dma_cache_wback ; 
 void* _dma_cache_wback_inv ; 
 int /*<<< orphan*/  dcache_lsize ; 
 int dcache_size ; 
 int /*<<< orphan*/  flush_cache_all ; 
 int /*<<< orphan*/  flush_cache_mm ; 
 int /*<<< orphan*/  flush_cache_page ; 
 int /*<<< orphan*/  flush_cache_range ; 
 int /*<<< orphan*/  flush_data_cache_page ; 
 void* flush_icache_range ; 
 int /*<<< orphan*/  icache_lsize ; 
 int icache_size ; 
 int /*<<< orphan*/  local_flush_data_cache_page ; 
 void* local_flush_icache_range ; 
 int /*<<< orphan*/  local_r3k_flush_data_cache_page ; 
 int /*<<< orphan*/  printk (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r3k___flush_cache_all ; 
 void* r3k_dma_cache_wback_inv ; 
 int /*<<< orphan*/  r3k_flush_cache_all ; 
 int /*<<< orphan*/  r3k_flush_cache_mm ; 
 int /*<<< orphan*/  r3k_flush_cache_page ; 
 int /*<<< orphan*/  r3k_flush_cache_range ; 
 int /*<<< orphan*/  r3k_flush_data_cache_page ; 
 void* r3k_flush_icache_range ; 
 int /*<<< orphan*/  r3k_flush_kernel_vmap_range ; 
 int /*<<< orphan*/  r3k_probe_cache () ; 

void r3k_cache_init(void)
{
	extern void build_clear_page(void);
	extern void build_copy_page(void);

	r3k_probe_cache();

	flush_cache_all = r3k_flush_cache_all;
	__flush_cache_all = r3k___flush_cache_all;
	flush_cache_mm = r3k_flush_cache_mm;
	flush_cache_range = r3k_flush_cache_range;
	flush_cache_page = r3k_flush_cache_page;
	flush_icache_range = r3k_flush_icache_range;
	local_flush_icache_range = r3k_flush_icache_range;
	__flush_icache_user_range = r3k_flush_icache_range;
	__local_flush_icache_user_range = r3k_flush_icache_range;

	__flush_kernel_vmap_range = r3k_flush_kernel_vmap_range;

	local_flush_data_cache_page = local_r3k_flush_data_cache_page;
	flush_data_cache_page = r3k_flush_data_cache_page;

	_dma_cache_wback_inv = r3k_dma_cache_wback_inv;
	_dma_cache_wback = r3k_dma_cache_wback_inv;
	_dma_cache_inv = r3k_dma_cache_wback_inv;

	printk("Primary instruction cache %ldkB, linesize %ld bytes.\n",
		icache_size >> 10, icache_lsize);
	printk("Primary data cache %ldkB, linesize %ld bytes.\n",
		dcache_size >> 10, dcache_lsize);

	build_clear_page();
	build_copy_page();
}