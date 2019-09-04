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
 int /*<<< orphan*/  SB_PRINT_I32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_I64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_QUERIES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_PRINT_TIME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STATS_BUFF_SIZE ; 
 int /*<<< orphan*/  active_aio_queries ; 
 int /*<<< orphan*/  active_gathers ; 
 int /*<<< orphan*/  aio_query_timeout_value ; 
 int /*<<< orphan*/  alloc_tree_nodes ; 
 int /*<<< orphan*/  append_to_binlog_time ; 
 int /*<<< orphan*/  bad_image_cache_max_living_time ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  binlog_index_loading_time ; 
 int /*<<< orphan*/  binlog_load_time ; 
 int /*<<< orphan*/  booting_time ; 
 int /*<<< orphan*/  choose_binlog_options ; 
 int /*<<< orphan*/  choose_reading_binlog_errors ; 
 int /*<<< orphan*/  cmd_stats ; 
 int /*<<< orphan*/  cmd_version ; 
 int /*<<< orphan*/  expired_aio_queries ; 
 int /*<<< orphan*/  gather_timeouts ; 
 int /*<<< orphan*/  get_file_queries ; 
 int /*<<< orphan*/  get_hide_queries ; 
 int /*<<< orphan*/  get_misses ; 
 int /*<<< orphan*/  get_queries ; 
 int /*<<< orphan*/  get_volume_misses ; 
 int /*<<< orphan*/  http_queries ; 
 int /*<<< orphan*/  idx_docs ; 
 int /*<<< orphan*/  index_load_time ; 
 int /*<<< orphan*/  index_size ; 
 int /*<<< orphan*/  max_aio_connections_per_disk ; 
 int /*<<< orphan*/  max_immediately_reply_filesize ; 
 int /*<<< orphan*/  max_metafiles_bytes ; 
 int /*<<< orphan*/  md5_mode ; 
 int /*<<< orphan*/  metafiles ; 
 int /*<<< orphan*/  metafiles_bytes ; 
 int /*<<< orphan*/  metafiles_cache_hits ; 
 int /*<<< orphan*/  metafiles_cancelled ; 
 int /*<<< orphan*/  metafiles_crc32_errors ; 
 int /*<<< orphan*/  metafiles_load_errors ; 
 int /*<<< orphan*/  metafiles_unloaded ; 
 int /*<<< orphan*/  one_pix_transparent_errors ; 
 int /*<<< orphan*/  open_replicas_time ; 
 int /*<<< orphan*/  redirect_retries ; 
 int /*<<< orphan*/  redirect_retries_content_type ; 
 int /*<<< orphan*/  redirect_retries_corrupted ; 
 int /*<<< orphan*/  redirect_retries_local_id ; 
 int /*<<< orphan*/  redirect_retries_meta_aio ; 
 int /*<<< orphan*/  redirect_retries_secret ; 
 int /*<<< orphan*/  redirect_retries_type ; 
 int /*<<< orphan*/  reoder_binlog_files_time ; 
 int /*<<< orphan*/  safe_div (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_memory (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  sb_prepare (TYPE_1__*,struct connection*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sb_printf (TYPE_1__*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  scandir_time ; 
 int /*<<< orphan*/  snapshot_size ; 
 int /*<<< orphan*/  stats_buff ; 
 int /*<<< orphan*/  statvfs_calls ; 
 int /*<<< orphan*/  too_many_aio_connections_errors ; 
 int /*<<< orphan*/  tot_aio_fsync_queries ; 
 int /*<<< orphan*/  tot_aio_loaded_bytes ; 
 int /*<<< orphan*/  tot_aio_queries ; 
 int /*<<< orphan*/  tot_docs ; 
 int /*<<< orphan*/  total_aio_time ; 
 int /*<<< orphan*/  volumes ; 
 int /*<<< orphan*/  x_accel_redirects ; 

int storage_prepare_stats (struct connection *c) {
  stats_buffer_t sb;
  sb_prepare (&sb, c, stats_buff, STATS_BUFF_SIZE);
  sb_memory (&sb, AM_GET_MEMORY_USAGE_SELF + AM_GET_MEMORY_USAGE_OVERALL);

  SB_PRINT_TIME(booting_time);
  SB_PRINT_TIME(scandir_time);
  SB_PRINT_TIME(reoder_binlog_files_time);
  SB_PRINT_TIME(open_replicas_time);
  SB_PRINT_TIME(binlog_index_loading_time);
  SB_PRINT_TIME(append_to_binlog_time);
  SB_PRINT_TIME(binlog_load_time);
  SB_PRINT_TIME(index_load_time);
  sb_printf (&sb,
      "volumes\t%d\n"
      "binlog_disabled\t%d\n"
      "index_loaded_bytes\t%lld\n"
      "index_size\t%lld\n"
/*
      "binlog_original_size\t%lld\n"
      "binlog_loaded_bytes\t%lld\n"
      "binlog_load_time\t%.6fs\n"
      "current_binlog_size\t%lld\n"
      "binlog_uncommitted_bytes\t%d\n"
      "binlog_path\t%s\n"
      "binlog_first_timestamp\t%d\n"
      "binlog_read_timestamp\t%d\n"
      "binlog_last_timestamp\t%d\n"
      "index_loaded_bytes\t%lld\n"
      "index_size\t%lld\n"
      "index_path\t%s\n"
      "index_load_time\t%.6fs\n"
*/
      "cmd_version\t%lld\n"
      "cmd_stats\t%lld\n"
      "tree_nodes\t%d\n"
      "tot_docs\t%lld\n"
      "idx_docs\t%lld\n"
      "md5_mode\t%d\n"
      "max_immediately_reply_filesize\t%d\n"
      "metafiles\t%d\n"
      "metafiles_unloaded\t%lld\n"
      "metafiles_load_errors\t%lld\n"
      "metafiles_crc32_errors\t%lld\n"
      "metafiles_cancelled\t%lld\n"
      "choose_reading_binlog_errors\t%lld\n"
      "metafiles_bytes\t%d\n"
      "max_metafiles_bytes\t%d\n"
      "tot_aio_queries\t%lld\n"
      "active_aio_queries\t%lld\n"
      "expired_aio_queries\t%lld\n"
      "avg_aio_query_time\t%.6f\n"
      "aio_bytes_loaded\t%lld\n"
      "aio_query_timeout\t%.3lfs\n"
      "metafiles_cache_hits\t%lld\n",
    volumes,
    binlog_disabled,
    snapshot_size,
    index_size,
/*
    binlog_loaded_size,
    log_readto_pos - jump_log_pos,
    binlog_load_time,
    log_pos,
    log_uncommitted,
    binlogname ? (sizeof(binlogname) < 250 ? binlogname : "(too long)") : "(none)",
    log_first_ts,
    log_read_until,
    log_last_ts,
		idx_loaded_bytes,
		engine_snapshot_size,
    engine_snapshot_name,
    index_load_time,
*/
    cmd_version,
    cmd_stats,
    alloc_tree_nodes,
    tot_docs,
    idx_docs,
    md5_mode,
    max_immediately_reply_filesize,
    metafiles,
    metafiles_unloaded,
    metafiles_load_errors,
    metafiles_crc32_errors,
    metafiles_cancelled,
    choose_reading_binlog_errors,
    metafiles_bytes,
    max_metafiles_bytes,
    tot_aio_queries,
    active_aio_queries,
    expired_aio_queries,
    safe_div (total_aio_time, tot_aio_queries),
    tot_aio_loaded_bytes,
    aio_query_timeout_value,
    metafiles_cache_hits
    );
  SB_PRINT_I32(max_aio_connections_per_disk);

  SB_PRINT_QUERIES(http_queries);
  SB_PRINT_QUERIES(get_queries);
  SB_PRINT_QUERIES(get_file_queries);
  SB_PRINT_QUERIES(get_hide_queries);
  SB_PRINT_I64(get_misses);
  SB_PRINT_I64(get_volume_misses);

  SB_PRINT_I64(x_accel_redirects);
  SB_PRINT_I64(one_pix_transparent_errors);
  SB_PRINT_I64(too_many_aio_connections_errors);
  SB_PRINT_I64(redirect_retries);
  SB_PRINT_I64(redirect_retries_meta_aio);
  SB_PRINT_I64(redirect_retries_corrupted);
  SB_PRINT_I64(redirect_retries_secret);
  SB_PRINT_I64(redirect_retries_type);
  SB_PRINT_I64(redirect_retries_content_type);
  SB_PRINT_I64(redirect_retries_local_id);

  SB_PRINT_I64(statvfs_calls);

  SB_PRINT_I32(active_gathers);
  SB_PRINT_I64(gather_timeouts);
  SB_PRINT_I64(tot_aio_fsync_queries);
  SB_PRINT_I32(bad_image_cache_max_living_time);

  sb_printf (&sb, "choose_binlog_options\t%s\n", choose_binlog_options);
  sb_printf (&sb, "version\t%s\n", FullVersionStr);

  return sb.pos;
}