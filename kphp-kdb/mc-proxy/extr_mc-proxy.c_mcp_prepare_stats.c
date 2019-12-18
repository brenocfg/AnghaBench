#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct connection {int dummy; } ;
struct TYPE_4__ {double cluster_name; int cluster_no; int cluster_mode; int get_timeout; int set_timeout; int /*<<< orphan*/  points_num; int /*<<< orphan*/  tot_buckets; } ;
struct TYPE_3__ {int config_loaded_at; int config_bytes; double config_md5_hex; int /*<<< orphan*/  clusters_num; } ;

/* Variables and functions */
 TYPE_2__* CC ; 
 TYPE_1__* CurConf ; 
 int /*<<< orphan*/  active_queries ; 
 int /*<<< orphan*/  client_errors_received ; 
 char* config_filename ; 
 int /*<<< orphan*/  diagonal_forwarded_total ; 
 int /*<<< orphan*/  diagonal_received_queries ; 
 int /*<<< orphan*/  dropped_overflow_responses ; 
 scalar_t__ dyn_cur ; 
 scalar_t__ dyn_first ; 
 scalar_t__ dyn_last ; 
 int /*<<< orphan*/  dyn_update_stats () ; 
 int /*<<< orphan*/  errors_received ; 
 int /*<<< orphan*/  expired_forwarded_queries ; 
 char* extension_name ; 
 int freed_blocks ; 
 char* freed_bytes ; 
 int /*<<< orphan*/  immediate_forwarded_queries ; 
 int prepare_stats (struct connection*,char*,int) ; 
 scalar_t__ search_stats (char*,int) ; 
 scalar_t__ snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  tot_forwarded_queries ; 
 int /*<<< orphan*/  tot_skipped_answers ; 
 int /*<<< orphan*/  total_connect_failures ; 
 int /*<<< orphan*/  total_failed_connections ; 
 char* wasted_blocks ; 
 int wasted_bytes ; 

int mcp_prepare_stats (struct connection *c, char *stats_buffer, int stats_buffer_len) {
  dyn_update_stats();
  int stats_len = prepare_stats (c, stats_buffer, stats_buffer_len);
  if (*extension_name) {
    stats_len += snprintf (stats_buffer + stats_len, stats_buffer_len - stats_len, "extension\t%s\n", extension_name);
  }
  stats_len += snprintf (stats_buffer + stats_len, stats_buffer_len - stats_len,
    "heap_allocated\t%ld\n"
    "heap_max\t%ld\n"
    "wasted_heap_blocks\t%d\n"
    "wasted_heap_bytes\t%ld\n"
    "free_heap_blocks\t%d\n"
    "free_heap_bytes\t%ld\n"
    "config_filename\t%s\n"
    "config_loaded_at\t%d\n"
    "config_size\t%d\n"
    "config_md5\t%s\n"
    "cluster_name\t%s\n"
    "cluster_number\t%d\n"
    "cluster_mode\t0x%04x\n"
    "get_timeout\t%.3f\n"
    "set_timeout\t%.3f\n"
    "tot_clusters\t%d\n"
    "cluster_size\t%d\n"
    "points_per_server\t%d\n"
    "active_queries\t%d\n"
    "total_forwarded_queries\t%lld\n"
    "expired_forwarded_queries\t%lld\n"
    "diagonal_received_queries\t%lld\n"
    "diagonal_forwarded_total\t%lld\n"
    "immediate_forwarded_queries\t%lld\n"
    "dropped_overflow_responses\t%lld\n"
    "tot_skipped_answers\t%lld\n"
    "errors_received\t%lld\n"
    "client_errors_received\t%lld\n"
    "total_failed_connections\t%lld\n"
    "total_connect_failures\t%lld\n",
    (long)(dyn_cur - dyn_first),
    (long)(dyn_last - dyn_first),
    wasted_blocks,
    wasted_bytes,
    freed_blocks,
    freed_bytes,
    config_filename,
    CurConf->config_loaded_at,
    CurConf->config_bytes,
    CurConf->config_md5_hex,
    CC->cluster_name,
    CC->cluster_no,
    CC->cluster_mode,
    CC->get_timeout,
    CC->set_timeout,
    CurConf->clusters_num,
    CC->tot_buckets,
    CC->points_num,
    active_queries,
    tot_forwarded_queries,
    expired_forwarded_queries,
    diagonal_received_queries,
    diagonal_forwarded_total,
    immediate_forwarded_queries,
    dropped_overflow_responses,
    tot_skipped_answers,
    errors_received,
    client_errors_received,
    total_failed_connections,
    total_connect_failures);
#ifdef SEARCH_MODE_ENABLED
  stats_len += search_stats (stats_buffer + stats_len, stats_buffer_len - stats_len);
#endif
  return stats_len;
}