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
struct TYPE_11__ {char* filename; scalar_t__ file_size; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ MAX_ZALLOC ; 
 scalar_t__ PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  STATS_SCHEMA_V1 ; 
 TYPE_3__* Snapshot ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int auto_create_new_versions ; 
 int /*<<< orphan*/  backlog ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  binlog_load_time ; 
 scalar_t__ binlog_loaded_size ; 
 char* binlogname ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 int dynamic_data_buffer_size ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_5__* engine_replica ; 
 char* engine_snapshot_name ; 
 int /*<<< orphan*/  engine_snapshot_replica ; 
 scalar_t__ engine_snapshot_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ get_binlog_start_pos (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_my_ipv4 () ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_load_time ; 
 int index_mode ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_log_data (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_server_PID (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ init_stats_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int load_index (TYPE_3__*) ; 
 int log_readto_pos ; 
 int log_ts_interval ; 
 int /*<<< orphan*/  max_counters_growth_percent ; 
 int maxconn ; 
 int /*<<< orphan*/  no_argument ; 
 int now ; 
 TYPE_4__* open_binlog (TYPE_5__*,scalar_t__) ; 
 TYPE_3__* open_recent_snapshot (int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 scalar_t__ port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  required_argument ; 
 scalar_t__ reverse_index_mode ; 
 scalar_t__ reverse_index_pos ; 
 int /*<<< orphan*/  save_index () ; 
 scalar_t__ server_socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  start_server () ; 
 void* start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  test_mode ; 
 void* time (int /*<<< orphan*/ ) ; 
 int today_start ; 
 scalar_t__ udp_enabled ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int verbosity ; 

int main (int argc, char *argv[]) {
  int i;
  /*
  strcpy(config_filename, "startx-engine.rc");
  */

  set_debug_handlers ();
  progname = argv[0];

  index_mode = 0;
  if (strstr (progname, "statsx-index") != NULL) {
    index_mode = 1;
  }

  auto_create_new_versions = 1;

  parse_option (0, no_argument, 0, 'f', "=memcache_auto_answer_mode");
  parse_option ("test", no_argument, 0, 'T', "test mode");
  parse_option ("no-user-id", no_argument, 0, 'm', "ignore user id");
  parse_option ("index", no_argument, 0, 'i', "reindex");
  parse_option ("high-memory", no_argument, 0, 'M', "memory usage to reindex");
  parse_option ("no-version", no_argument, 0, 'y', "counters are valid until disabled by hands");
  parse_option ("custom-version", no_argument, 0, 'x', "use yyyymmdd as counter version. Includes [--no-version]");
  parse_option ("monthly", no_argument, 0, 'E', "enable monthly stat");
  parse_option ("no-set-timezone", no_argument, 0, 't', "ignore all set timezone events");
  parse_option ("day-start-version", no_argument, 0, 'D', "use unixtime at 0:00 as counter version");
  parse_option ("counter-growth", required_argument, 0, 'P', "counter hash table growth in percents (default %lf)", max_counters_growth_percent);
  parse_option ("default-timezone", required_argument, 0, 'S', "default timezone (hours offset from GMT)");
  parse_option ("cyclic-binlog", required_argument, 0, 1000, "use binlog in cyclic mode");
  
  parse_engine_options_long (argc, argv, f_parse_option);
  if (argc != optind + 1 && argc != optind + 2) {
    usage ();
    return 2;
  }

  if (verbosity >= 3) {
    if (index_mode) {
      fprintf (stderr, "Starting in index mode...\n");
    }
  }
/*
  types_count = 0;
*/
//  max_binlog_size = 170;

  if (raise_file_rlimit(maxconn + 16) < 0 && !test_mode) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit(1);
  }

  if (port < PRIVILEGED_TCP_PORTS) {
    sfd = server_socket (port, settings_addr, backlog, 0);
    if (sfd < 0) {
      fprintf(stderr, "cannot open server socket at port %d: %m\n", port);
      exit(1);
    }
  }

  aes_load_pwd_file (0);

  if (change_user(username) < 0 && !test_mode) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit(1);
  }

  if (MAX_ZALLOC > 0) {
  } else {
    dynamic_data_buffer_size = (1 << 23);
  }
  init_dyn_data();
  if (udp_enabled) {
    init_server_PID (get_my_ipv4 (), port);
  }
/*
  reload_config();
*/

  if (engine_preload_filelist (argv[optind], binlogname) < 0) {
    fprintf (stderr, "cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }


  log_ts_interval = 10;
  int tt;
  today_start = tt = time(0);
  today_start -= tt % 86400;

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

  index_load_time = -get_utime(CLOCK_MONOTONIC);

  i = load_index (Snapshot);

  index_load_time += get_utime(CLOCK_MONOTONIC);

  if (i < 0) {
    fprintf (stderr, "fatal: error %d while loading index file %s\n", i, engine_snapshot_name);
    exit (1);
  }


  if (verbosity) {
    fprintf (stderr, "Reading binlog from position %lld\n", jump_log_pos);
  }

  if (reverse_index_mode) {
    assert (init_stats_data (STATS_SCHEMA_V1) >= 0);
    if (reverse_index_pos) {
      jump_log_pos = reverse_index_pos;
    } else {
      jump_log_pos = get_binlog_start_pos (engine_replica, 0, 0) + 36;
    }
  }

  log_ts_interval = 10;
  today_start = now = time(0);
  today_start -= now % 86400;
  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    fprintf (stderr, "fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, jump_log_pos);
    exit (1);
  }

  binlogname = Binlog->info->filename;

  if (verbosity) {
    fprintf (stderr, "replaying binlog file %s (size %lld)\n", binlogname, Binlog->info->file_size);
  }
  binlog_load_time = get_utime(CLOCK_MONOTONIC);

  clear_log();

  init_log_data (jump_log_pos, jump_log_ts, jump_log_crc32);

  i = replay_log (0, 1);

  if (i < 0) {
    fprintf (stderr, "fatal: error reading binlog\n");
    exit (1);
  }

  binlog_load_time = get_utime(CLOCK_MONOTONIC) - binlog_load_time;
  binlog_loaded_size = log_readto_pos - jump_log_pos;

  if (!binlog_disabled) {
    clear_read_log();
  }


  if (index_mode) {
    if (verbosity >= 1) {
      fprintf (stderr, "Saving index...\n");
    }
    if (!reverse_index_mode) {
      save_index ();
    } else {
      assert (0);
    }
  } else {
    clear_write_log();
    start_time = time(0);

    start_server();
  }

  return 0;
}