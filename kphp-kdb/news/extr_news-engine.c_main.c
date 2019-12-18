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
struct TYPE_13__ {long long offset; TYPE_2__* info; } ;
struct TYPE_12__ {TYPE_1__* info; } ;
struct TYPE_11__ {char* filename; int log_pos; int /*<<< orphan*/  file_size; } ;
struct TYPE_10__ {char* filename; scalar_t__ file_size; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 int /*<<< orphan*/  CD_ENGINE ; 
 int /*<<< orphan*/  CD_INDEXER ; 
 scalar_t__ DEFAULT_MAX_ALLOCATED_METAFILES_SIZE ; 
 int /*<<< orphan*/  MAX_NEWS_DAYS ; 
 TYPE_3__* Snapshot ; 
 int /*<<< orphan*/  aes_pwd_file ; 
 int binlog_crc32_verbosity_level ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  binlog_load_time ; 
 int binlog_loaded_size ; 
 int binlog_read ; 
 char* binlogname ; 
 scalar_t__ check_index_mode ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 int /*<<< orphan*/  cstatus_binlog_name (char*) ; 
 int /*<<< orphan*/  engine_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_5__* engine_replica ; 
 char* engine_snapshot_name ; 
 int /*<<< orphan*/  engine_snapshot_replica ; 
 scalar_t__ engine_snapshot_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  index_load_time ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  init_common_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_log_data (long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 long long jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 void* last_collect_garbage_time ; 
 int load_index (TYPE_3__*) ; 
 long long log_readto_pos ; 
 scalar_t__ log_ts_interval ; 
 int max_news_days ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 void* min_logevent_time ; 
 int /*<<< orphan*/  mytime () ; 
 int /*<<< orphan*/  news_engine ; 
 int /*<<< orphan*/  no_argument ; 
 TYPE_4__* open_binlog (TYPE_5__*,long long) ; 
 TYPE_3__* open_recent_snapshot (int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char*,...) ; 
 int /*<<< orphan*/  perror (char*) ; 
 char* progname ; 
 scalar_t__ regenerate_index_mode ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  required_argument ; 
 int /*<<< orphan*/  save_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  start_server () ; 
 void* start_time ; 
 int /*<<< orphan*/  stderr ; 
 int strlen (char*) ; 
 void* time (int /*<<< orphan*/ ) ; 
 scalar_t__ truncate (char*,long long) ; 
 int /*<<< orphan*/  usage () ; 
 scalar_t__ verbosity ; 

int main (int argc, char *argv[]) {
  int i;
  set_debug_handlers ();
  progname = argv[0];

  parse_option ("days", required_argument, 0, 't', "Number of days to keep news (default %d)", MAX_NEWS_DAYS);
  parse_option ("index", no_argument, 0, 'i', "reindex");
  parse_option ("metafiles-memory", required_argument, 0, 'C', "memory for metafiles cache (default %lld)", (long long)DEFAULT_MAX_ALLOCATED_METAFILES_SIZE);
  parse_option ("check-index", no_argument, 0, 'L', "check index mode");
  parse_option ("regenerate-index", no_argument, 0, 'R', "regenerate index mode");

  parse_engine_options_long (argc, argv, f_parse_option);
  if (argc != optind + 1 && argc != optind + 2) {
    usage();
    return 2;
  }

  if (regenerate_index_mode) {
    check_index_mode = 0;
  }

  if (strlen (argv[0]) >= 5 && memcmp ( argv[0] + strlen (argv[0]) - 5, "index" , 5) == 0) {
    index_mode++;
  }

  engine_init (&news_engine, aes_pwd_file, index_mode);

  if (engine_preload_filelist (argv[optind], binlogname) < 0) {
    fprintf (stderr, "cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }

  log_ts_interval = 0;

  //Snapshot reading
  Snapshot = open_recent_snapshot (engine_snapshot_replica);

  if (Snapshot) {
    engine_snapshot_name = Snapshot->info->filename;
    engine_snapshot_size = Snapshot->info->file_size;

    if (verbosity) {
      fprintf (stderr, "load index file %s (size %lld)\n", engine_snapshot_name, engine_snapshot_size);
    }
  } else {
    engine_snapshot_name = NULL;
    engine_snapshot_size = 0;
  }

  index_load_time = -mytime();

  i = load_index (Snapshot);

  index_load_time += mytime();

  if (i < 0) {
    fprintf (stderr, "fatal: error %d while loading index file %s\n", i, engine_snapshot_name);
    exit (1);
  }

  //close_snapshot (Snapshot, 1);

  if (verbosity) {
    fprintf (stderr, "load index: done, jump_log_pos=%lld, time %.06lfs\n",
       jump_log_pos, index_load_time);
  }

  //Binlog reading
  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    fprintf (stderr, "fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, jump_log_pos);
    exit (1);
  }
  binlogname = Binlog->info->filename;
  
  init_common_data (0, index_mode ? CD_INDEXER : CD_ENGINE);
  cstatus_binlog_name (engine_replica->replica_prefix);

  if (verbosity) {
    fprintf (stderr, "replaying binlog file %s (size %lld) from position %lld (crc32=%u, ts=%d)\n", binlogname, Binlog->info->file_size, jump_log_pos, jump_log_crc32, jump_log_ts);
  }

  binlog_load_time = -mytime();

  clear_log();

  init_log_data (jump_log_pos, jump_log_ts, jump_log_crc32);

  if (verbosity) { fprintf (stderr, "replay log events started\n");}

  min_logevent_time = time(0) - (max_news_days + 1) * 86400;
  i = replay_log (0, 1);
  if (verbosity) { fprintf (stderr, "replay log events finished\n");}

  binlog_load_time += mytime();
  binlog_loaded_size = log_readto_pos - jump_log_pos;

  if (!binlog_disabled) {
    clear_read_log();
  }

  if (i == -2) {
    long long true_readto_pos = log_readto_pos - Binlog->info->log_pos + Binlog->offset;
    fprintf (stderr, "REPAIR: truncating %s at log position %lld (file position %lld)\n", Binlog->info->filename, log_readto_pos, true_readto_pos);
    if (truncate (Binlog->info->filename, true_readto_pos) < 0) {
      perror ("truncate()");
      exit (2);
    }
  } else if (i < 0) {
    fprintf (stderr, "fatal: error reading binlog\n");
    exit (1);
  }
  binlog_read = 1;
  binlog_crc32_verbosity_level = 5;

  //if (verbosity) {
  //  fprintf (stderr, "replay binlog file: done, log_pos=%lld, alloc_mem=%ld, time %.06lfs\n",
  //           (long long) log_pos, (long) get_memory_used (), binlog_load_time);
  //}


  clear_write_log();
  last_collect_garbage_time = start_time = time(0);
  check_index_mode = 0;

  if (index_mode) {
    save_index (0);
  } else {
    start_server ();
  }

  return 0;
}