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
struct connection {int dummy; } ;
struct TYPE_5__ {int pos; } ;
typedef  TYPE_1__ stats_buffer_t ;

/* Variables and functions */
 scalar_t__ AM_GET_MEMORY_USAGE_OVERALL ; 
 scalar_t__ AM_GET_MEMORY_USAGE_SELF ; 
 int /*<<< orphan*/  FullVersionStr ; 
 int /*<<< orphan*/  SB_BINLOG ; 
 int /*<<< orphan*/  SB_INDEX ; 
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  active_aio_queries ; 
 int /*<<< orphan*/  alloc_tree_nodes ; 
 int /*<<< orphan*/  counters_prime ; 
 int /*<<< orphan*/  deleted_by_lru ; 
 int /*<<< orphan*/  expired_aio_queries ; 
 int /*<<< orphan*/  index_size ; 
 int /*<<< orphan*/  max_counters ; 
 int /*<<< orphan*/  memory_to_index ; 
 int /*<<< orphan*/  percent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_memory (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sb_prepare (TYPE_1__*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snapshot_loading_average_blocking_read_bytes ; 
 int /*<<< orphan*/  snapshot_loading_blocking_read_calls ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  tot_aio_fails ; 
 int /*<<< orphan*/  tot_aio_loaded_bytes ; 
 int tot_aio_queries ; 
 int /*<<< orphan*/  tot_counter_instances ; 
 int /*<<< orphan*/  tot_counters ; 
 int /*<<< orphan*/  tot_counters_allocated ; 
 int /*<<< orphan*/  tot_memory_allocated ; 
 int /*<<< orphan*/  tot_user_metafile_bytes ; 
 int /*<<< orphan*/  tot_user_metafiles ; 
 int /*<<< orphan*/  tot_views ; 
 int total_aio_time ; 

int stats_prepare_stats (struct connection *c) {
  stats_buffer_t sb;
  sb_prepare (&sb, c, stats_buff, STATS_BUFF_SIZE);
  sb_memory (&sb, AM_GET_MEMORY_USAGE_SELF + AM_GET_MEMORY_USAGE_OVERALL);  
  SB_BINLOG;
  SB_INDEX;

  sb_printf (&sb,
      "snapshot_loading_average_blocking_read_bytes\t%.6f\n"
      "snapshot_loading_blocking_read_calls\t%d\n"
      "tot_user_metafiles\t%d\n"
      "tot_user_metafile_bytes\t%lld\n"
      "counters\t%d\n"
      "counters_percent\t%.6f\n"
      "counters_prime\t%d\n"
      "total_views\t%lld\n"
      "tree_nodes_allocated\t%d\n"
      "counter_instances\t%d\n"
      "counter_instances_percent\t%.6f\n"
      "allocated_counter_instances\t%d\n"
      "deleted_by_LRU\t%lld\n"
      "allocated_memory\t%lld\n"
      "tot_aio_queries\t%lld\n"
      "active_aio_queries\t%lld\n"
      "expired_aio_queries\t%lld\n"
      "avg_aio_query_time\t%.6f\n"
      "aio_bytes_loaded\t%lld\n"
      "tot_aio_queries\t%lld\n"
      "tot_aio_fails\t%lld\n"
      "memory_to_index\t%lld\n"
      "version\t%s\n",
    snapshot_loading_average_blocking_read_bytes,
    snapshot_loading_blocking_read_calls,
    tot_user_metafiles,
    tot_user_metafile_bytes,
    tot_counters,
    percent (tot_counters, max_counters),
    counters_prime,
    tot_views,
    alloc_tree_nodes,
    tot_counter_instances,
    percent (tot_counter_instances, index_size),
    tot_counters_allocated,
    deleted_by_lru,
    tot_memory_allocated,
    tot_aio_queries,
    active_aio_queries,
    expired_aio_queries,
    tot_aio_queries > 0 ? total_aio_time / tot_aio_queries : 0,
    tot_aio_loaded_bytes,
    tot_aio_queries,
    tot_aio_fails,
    memory_to_index,
    FullVersionStr
    );
  return sb.pos;
}