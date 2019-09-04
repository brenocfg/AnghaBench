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
typedef  int /*<<< orphan*/  stats_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  allocated_metafile_bytes ; 
 int /*<<< orphan*/  expired_aio_queries ; 
 int /*<<< orphan*/  metafile_number ; 
 int /*<<< orphan*/  metafiles_cache_miss ; 
 int /*<<< orphan*/  metafiles_cache_ok ; 
 int /*<<< orphan*/  metafiles_load_errors ; 
 int /*<<< orphan*/  metafiles_load_success ; 
 int /*<<< orphan*/  metafiles_loaded ; 
 int /*<<< orphan*/  metafiles_unload_LRU ; 
 int /*<<< orphan*/  sb_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tot_aio_loaded_bytes ; 
 int /*<<< orphan*/  tot_records ; 
 int /*<<< orphan*/  use_query_fails ; 

void custom_prepare_stats (stats_buffer_t *sb) {
  sb_printf (sb,
    "total_index_entries\t%lld\n"
    "total_metafiles\t%d\n"
    "metafiles_loaded\t%d\n"
    "metafiles_allocated_bytes\t%lld\n"
    "metafiles_unloaded_LRU\t%lld\n"
    "metafiles_load_errors\t%lld\n"
    "metafiles_load_success\t%lld\n"
    "metafiles_load_timeout\t%lld\n"
    "metafiles_total_loaded_bytes\t%lld\n"
    "metafiles_LRU_fails\t%d\n"
    "metafiles_cache_miss\t%lld\n"
    "metafiles_cache_ok\t%lld\n",
    tot_records,
    metafile_number,
    metafiles_loaded,
    allocated_metafile_bytes,
    metafiles_unload_LRU,
    metafiles_load_errors,
    metafiles_load_success,
    expired_aio_queries,
    tot_aio_loaded_bytes,
    use_query_fails,
    metafiles_cache_miss,
    metafiles_cache_ok);
}