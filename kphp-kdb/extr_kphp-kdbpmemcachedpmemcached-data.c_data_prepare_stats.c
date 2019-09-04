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
 scalar_t__ HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  cache_deletes ; 
 scalar_t__ cache_free ; 
 int /*<<< orphan*/  cache_miss ; 
 int /*<<< orphan*/  cache_ok ; 
 int /*<<< orphan*/  cache_size ; 
 int /*<<< orphan*/  cache_update ; 
 int /*<<< orphan*/  entry_memory ; 
 int /*<<< orphan*/  get_entry_cnt () ; 
 int /*<<< orphan*/  init_memory ; 
 int /*<<< orphan*/  memory_for_cache ; 
 int /*<<< orphan*/  memory_for_entries ; 
 int /*<<< orphan*/  memory_for_metafiles ; 
 int /*<<< orphan*/  sb_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void data_prepare_stats (stats_buffer_t *sb) {
  sb_printf (sb,
    "limit_entries_memory\t%lld\n"
    "limit_cache_memory\t%lld\n"
    "limit_metafiles_memory\t%lld\n"
    "cache_number\t%d\n"
    "cache_free\t%d\n"
    "cache_size\t%lld\n"
    "cache_ok\t%lld\n"
    "cache_updates\t%lld\n"
    "cache_miss\t%lld\n"
    "cache_deletes\t%lld\n"
    "entry_number\t%d\n"
    "entry_size\t%lld\n"
    "init_size\t%lld\n",
    memory_for_entries,
    memory_for_cache,
    memory_for_metafiles,
    HASH_TABLE_SIZE - cache_free,
    cache_free,
    cache_size,
    cache_ok,
    cache_update,
    cache_miss,
    cache_deletes,
    get_entry_cnt (),
    entry_memory,
    init_memory);
}