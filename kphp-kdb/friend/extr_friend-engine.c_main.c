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
struct TYPE_11__ {scalar_t__ file_size; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 int /*<<< orphan*/  CD_ENGINE ; 
 int /*<<< orphan*/  CD_INDEXER ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ PRIVILEGED_TCP_PORTS ; 
 int /*<<< orphan*/  SIGRTMAX ; 
 TYPE_3__* Snapshot ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aes_pwd_file ; 
 int /*<<< orphan*/  backlog ; 
 int binlog_disabled ; 
 int /*<<< orphan*/  binlog_load_time ; 
 int /*<<< orphan*/  binlog_loaded_size ; 
 char* binlogname ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 int /*<<< orphan*/  close_snapshot (TYPE_3__*,int) ; 
 int /*<<< orphan*/  cstatus_binlog_name (char*) ; 
 int /*<<< orphan*/  dump_lists (int /*<<< orphan*/ ) ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_5__* engine_replica ; 
 char* engine_snapshot_name ; 
 int /*<<< orphan*/  engine_snapshot_replica ; 
 scalar_t__ engine_snapshot_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_my_ipv4 () ; 
 int /*<<< orphan*/  get_utime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_load_time ; 
 int index_mode ; 
 int /*<<< orphan*/  init_common_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_log_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_server_PID (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int load_index (TYPE_3__*) ; 
 int /*<<< orphan*/  log_readto_pos ; 
 int maxconn ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  no_argument ; 
 TYPE_4__* open_binlog (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* open_recent_snapshot (int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int*,char,char*) ; 
 scalar_t__ port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (int) ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  required_argument ; 
 scalar_t__ reverse_friends_mode ; 
 int /*<<< orphan*/  save_index (int /*<<< orphan*/ ) ; 
 scalar_t__ server_socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigrtmax_handler ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  stderr ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  test_mode ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 scalar_t__ udp_enabled ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 scalar_t__ verbosity ; 
 scalar_t__ w_split_mod ; 

int main (int argc, char *argv[]) {
  int i;

  signal (SIGRTMAX, sigrtmax_handler);
  set_debug_handlers ();

  parse_option ("test-mode", no_argument, 0, 'T', "test mode");
  parse_option ("ignore-delete-user", required_argument, 0, 'I', 0);
  parse_option ("dump-lists", required_argument, 0, 'W', "argument rem,mod. Dumps lists with specified rem mod mod");
  parse_option ("reverse", no_argument, 0, 'A', "reverse friends mode");
  parse_option ("index", no_argument, &index_mode, 'i', "index mode");
  parse_option (0, required_argument, 0, 'H', "heap size");

  progname = argv[0];
  parse_engine_options_long (argc, argv, f_parse_option);
  if (argc != optind + 1 && argc != optind + 2) {
    usage();
    return 2;
  }

  if (binlog_disabled > 1 || reverse_friends_mode) {
    binlog_disabled = 1;
  }

  if (strlen (argv[0]) >= 5 && memcmp ( argv[0] + strlen (argv[0]) - 5, "index" , 5) == 0) {
    index_mode = 1;
  }

  if (!w_split_mod && raise_file_rlimit(maxconn + 16) < 0 && !test_mode) {
    fprintf (stderr, "fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit(1);
  }

  if (!w_split_mod && port < PRIVILEGED_TCP_PORTS) {
    sfd = server_socket (port, settings_addr, backlog, 0);
    if (sfd < 0) {
      fprintf(stderr, "cannot open server socket at port %d: %m\n", port);
      exit(1);
    }
  }

  aes_load_pwd_file (aes_pwd_file);

  if (w_split_mod) {
    binlog_disabled = 1;
  }

  if (change_user(username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit(1);
  }

  init_dyn_data();
  if (udp_enabled) {
    init_server_PID (get_my_ipv4 (), port);
  }

  if (engine_preload_filelist (argv[optind], binlogname) < 0) {
    fprintf (stderr, "cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }
  
  init_common_data (0, index_mode ? CD_INDEXER : CD_ENGINE);
  cstatus_binlog_name (engine_replica->replica_prefix);

  Snapshot = open_recent_snapshot (engine_snapshot_replica);

  if (Snapshot) {
    engine_snapshot_name = strdup (Snapshot->info->filename);
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
    fprintf (stderr, "load index: done, jump_log_pos=%lld, time %.06lfs\n",
       jump_log_pos, index_load_time);
  }

  close_snapshot (Snapshot, 1);

  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    fprintf (stderr, "fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, 0LL);
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
  binlog_loaded_size = log_readto_pos;

  /*if (binlog_disabled != 1) {
    jump_log_pos = log_readto_pos;
    jump_log_ts = log_last_ts;
    jump_log_crc32 = ~log_crc32_complement;
    assert (jump_log_pos == log_crc32_pos);
    clear_read_log();
    close_binlog (Binlog);
    Binlog = 0;
  }*/

  if (binlog_disabled != 1) {
    clear_read_log();
  }

  clear_write_log();
  start_time = time(0);

  if (w_split_mod) {
    dump_lists (test_mode);
    return 0;
  }

  if (index_mode) {
    save_index (0);
  } else {
    start_server();
  }
  return 0;
}