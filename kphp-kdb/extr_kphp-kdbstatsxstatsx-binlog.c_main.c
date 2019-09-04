#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {char* replica_prefix; } ;
struct TYPE_13__ {TYPE_2__* info; } ;
struct TYPE_12__ {TYPE_1__* info; } ;
struct TYPE_11__ {char* filename; int /*<<< orphan*/  file_size; } ;
struct TYPE_10__ {char* filename; scalar_t__ file_size; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 TYPE_3__* Snapshot ; 
 scalar_t__ active_users_stats_replay_logevent ; 
 int /*<<< orphan*/  binlog_load_time ; 
 scalar_t__ binlog_loaded_size ; 
 char* binlogname ; 
 int /*<<< orphan*/  clear_log () ; 
 int cnt_id ; 
 int /*<<< orphan*/  count () ; 
 scalar_t__ dump_stats_replay_logevent ; 
 scalar_t__ dump_unique_cid_stats_replay_logevent ; 
 int end_time ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_5__* engine_replica ; 
 char* engine_snapshot_name ; 
 int /*<<< orphan*/  engine_snapshot_replica ; 
 scalar_t__ engine_snapshot_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_log_data (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int load_index (TYPE_3__*) ; 
 int log_readto_pos ; 
 int /*<<< orphan*/  mytime () ; 
 TYPE_4__* open_binlog (TYPE_5__*,scalar_t__) ; 
 TYPE_3__* open_recent_snapshot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  out ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 scalar_t__ replay_logevent ; 
 int /*<<< orphan*/  snapshot_load_time ; 
 int sscanf (int /*<<< orphan*/ ,char*,int*) ; 
 int start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int main (int argc, char *argv[]) {
  int use_index = 0;
  int i;
  out = stdout;
  replay_logevent = dump_stats_replay_logevent;
  while ((i = getopt (argc, argv, "c:hvlS:T:ui")) != -1) {
    switch (i) {
    case 'i':
      use_index = 1;
      break;
    case 'S':
      if (1 == sscanf(optarg, "%d", &i)) {
        start_time = i;
      }
      break;
    case 'T':
      if (1 == sscanf(optarg, "%d", &i)) {
        end_time = i;
      }
      break;
    case 'c':
      if (1 == sscanf(optarg, "%d", &i)) {
        cnt_id = i;
      }
      break;
    case 'v':
      verbosity++;
      break;
    case 'h':
      usage();
      return 2;
    case 'l':
      replay_logevent = dump_unique_cid_stats_replay_logevent;
      break;
    case 'u':
      replay_logevent = active_users_stats_replay_logevent;
      break;
    }
  }

  if (optind >= argc) {
    usage();
    return 2;
  }

  if (engine_preload_filelist ( argv[optind], binlogname) < 0) {
    fprintf (stderr, "cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }
  
  if (use_index) {
    vkprintf (1, "Use index\n");
    //Snapshot reading
    Snapshot = open_recent_snapshot (engine_snapshot_replica);

    if (Snapshot) {
      engine_snapshot_name = Snapshot->info->filename;
      engine_snapshot_size = Snapshot->info->file_size;
      vkprintf (1, "load index file %s (size %lld)\n", engine_snapshot_name, engine_snapshot_size);
    } else {
      engine_snapshot_name = NULL;
      engine_snapshot_size = 0;
    }

    snapshot_load_time = -get_utime(CLOCK_MONOTONIC);
    i = load_index (Snapshot);  
    snapshot_load_time += get_utime(CLOCK_MONOTONIC);
    if (i < 0) {
      fprintf (stderr, "fatal: error %d while loading index file %s\n", i, engine_snapshot_name);
      exit (1);
    }
  }


  if (verbosity>=3){
    fprintf (stderr, "engine_preload_filelist done\n");
  }
  vkprintf (3, "jump_log_pos = %lld\n", jump_log_pos);
  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    fprintf (stderr, "fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, jump_log_pos);
    exit (1);
  }

  binlogname = Binlog->info->filename;

  if (verbosity) {
    fprintf (stderr, "replaying binlog file %s (size %lld)\n", binlogname, Binlog->info->file_size);
  }
  binlog_load_time = -mytime();
  clear_log();
  init_log_data (jump_log_pos, jump_log_ts, jump_log_crc32);
  if (verbosity) {
    fprintf (stderr, "replay log events started\n");
  }

  i = replay_log (0, 1);
 
  if (verbosity) {
    fprintf (stderr, "replay log events finished\n");
  }

  binlog_load_time += mytime();
  binlog_loaded_size = log_readto_pos - jump_log_pos;

  if (replay_logevent == active_users_stats_replay_logevent || replay_logevent == dump_unique_cid_stats_replay_logevent) {
    count ();
  }

  return 0;
}