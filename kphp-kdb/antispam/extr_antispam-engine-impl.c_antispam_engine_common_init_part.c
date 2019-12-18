#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {char* replica_prefix; } ;
struct TYPE_14__ {TYPE_2__* info; } ;
struct TYPE_13__ {TYPE_1__* info; } ;
struct TYPE_12__ {char* filename; int /*<<< orphan*/  file_size; } ;
struct TYPE_11__ {int /*<<< orphan*/  file_size; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 TYPE_3__* Snapshot ; 
 int binlog_disabled ; 
 scalar_t__ binlog_load_time ; 
 scalar_t__ binlog_loaded_size ; 
 char* binlogname ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 int /*<<< orphan*/  close_snapshot (TYPE_3__*,int) ; 
 int /*<<< orphan*/  dyn_used_memory () ; 
 scalar_t__ engine_preload_filelist (char const*,char*) ; 
 TYPE_5__* engine_replica ; 
 char* engine_snapshot_name ; 
 int /*<<< orphan*/  engine_snapshot_replica ; 
 int /*<<< orphan*/  engine_snapshot_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_all (TYPE_3__*) ; 
 int /*<<< orphan*/  init_log_data (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 scalar_t__ log_pos ; 
 scalar_t__ log_readto_pos ; 
 TYPE_4__* open_binlog (TYPE_5__*,scalar_t__) ; 
 TYPE_3__* open_recent_snapshot (int /*<<< orphan*/ ) ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 scalar_t__ verbosity ; 

void antispam_engine_common_init_part (char const* index_fname) {
  if (engine_preload_filelist (index_fname, binlogname) < 0) {
    fprintf (stderr, "fatal: cannot preload files for binlog: '%s' and index: '%s'\n", binlogname, index_fname);
    exit (1);
  }

  Snapshot = open_recent_snapshot (engine_snapshot_replica);

  if (Snapshot) {
    engine_snapshot_name = strdup (Snapshot->info->filename);
    engine_snapshot_size = Snapshot->info->file_size;


    if (verbosity > 0) {
      fprintf (stderr, "load index file %s (size %lld)\n", engine_snapshot_name, engine_snapshot_size);
    }
  } else {
    engine_snapshot_name = NULL;
    engine_snapshot_size = 0;
  }

  init_all (Snapshot);
  close_snapshot (Snapshot, 1);

  // Load binlog
  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    fprintf (stderr, "fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, 0LL);
    exit (1);
  }

  binlogname = Binlog->info->filename;

  if (verbosity > 0) {
    fprintf (stderr, "replaying binlog file %s (size %lld)\n", binlogname, Binlog->info->file_size);
  }
  binlog_load_time = get_utime (CLOCK_MONOTONIC);

  clear_log();

  init_log_data (jump_log_pos, jump_log_ts, jump_log_crc32);

  if (verbosity > 0) {
    fprintf (stderr, "jump_log_pos = %lld\nreplay log events started\n", jump_log_pos);
  }

  int replay_log_result = replay_log (0, 1);

  if (binlog_disabled != 1) {
    clear_read_log();
  }

  if (replay_log_result < 0) {
    fprintf (stderr, "fatal: error reading binlog\n");
    exit (1);
  }
  if (verbosity > 0) {
    fprintf (stderr, "replay log events finished\n");
  }

  binlog_load_time = get_utime (CLOCK_MONOTONIC) - binlog_load_time;
  binlog_loaded_size = log_readto_pos - jump_log_pos;

  if (verbosity > 0) {
    fprintf (stderr, "replay binlog file: done, log_pos=%lld, used_z_memory=%ld, time %.06lfs\n",
            (long long)log_pos, dyn_used_memory (), binlog_load_time);
  }

  clear_write_log();

  start_time = time (0);
}