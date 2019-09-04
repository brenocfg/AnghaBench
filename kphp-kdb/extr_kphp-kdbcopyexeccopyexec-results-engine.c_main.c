#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  replica_prefix; } ;
struct TYPE_7__ {TYPE_1__* info; } ;
struct TYPE_6__ {char* filename; int /*<<< orphan*/  file_size; } ;

/* Variables and functions */
 void* BACKLOG ; 
 TYPE_2__* Binlog ; 
 scalar_t__ MAX_CONNECTIONS ; 
 int /*<<< orphan*/  aes_load_pwd_file (int /*<<< orphan*/ ) ; 
 void* atoi (void*) ; 
 void* backlog ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  binlog_load_time ; 
 scalar_t__ binlog_loaded_size ; 
 char* binlogname ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 int /*<<< orphan*/  copyexec_results_make_empty_binlog (char*) ; 
 int daemonize ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_3__* engine_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_log_data (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 scalar_t__ jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ log_readto_pos ; 
 void* logname ; 
 int max_lru_size ; 
 scalar_t__ maxconn ; 
 int /*<<< orphan*/  mytime () ; 
 TYPE_2__* open_binlog (TYPE_3__*,scalar_t__) ; 
 void* optarg ; 
 int optind ; 
 void* port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int sscanf (void*,char*,int*) ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int main (int argc, char *argv[]) {
  int i;
  char new_binlog = 0;
  set_debug_handlers ();

  progname = argv[0];
  while ((i = getopt (argc, argv, "a:b:c:l:p:dhu:vEM:")) != -1) {
    switch (i) {
    case 'E':
      new_binlog = 1;
      break;
    case 'M':
      if (sscanf (optarg, "%d", &i) != 1 || i < 1) {
        kprintf ("invalid -M arg: %s", optarg);
        usage ();
      }
      max_lru_size = i;
      break;
    case 'a':
      binlogname = optarg;
      break;
    case 'b':
      backlog = atoi (optarg);
      if (backlog <= 0) backlog = BACKLOG;
      break;
    case 'c':
      maxconn = atoi (optarg);
      if (maxconn <= 0 || maxconn > MAX_CONNECTIONS) {
	maxconn = MAX_CONNECTIONS;
      }
      break;
    case 'd':
      daemonize ^= 1;
      break;
    case 'h':
      usage ();
      break;
    case 'l':
      logname = optarg;
      break;
    case 'p':
      port = atoi(optarg);
      break;
    case 'u':
      username = optarg;
      break;
    case 'v':
      verbosity++;
      break;
    }
  }

  if (argc != optind + 1) {
    usage ();
  }

  if (raise_file_rlimit (maxconn + 16) < 0) {
    kprintf ("fatal: cannot raise open file limit to %d\n", maxconn+16);
    exit (1);
  }

  aes_load_pwd_file (0);

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  if (new_binlog) {
    copyexec_results_make_empty_binlog (argv[optind]);
    exit (0);
  }

  init_dyn_data ();

  if (engine_preload_filelist (argv[optind], binlogname) < 0) {
    kprintf ("cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }

  vkprintf (3, "engine_preload_filelist done\n");

  //Binlog reading
  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    kprintf ("fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, jump_log_pos);
    exit (1);
  }
  binlogname = Binlog->info->filename;
  vkprintf (1, "replaying binlog file %s (size %lld) from position %lld\n", binlogname, Binlog->info->file_size, jump_log_pos);
  binlog_load_time = -mytime();
  clear_log ();
  init_log_data (jump_log_pos, jump_log_ts, jump_log_crc32);
  vkprintf (1, "replay log events started\n");
  i = replay_log (0, 1);
  vkprintf (1, "replay log events finished\n");
  if (i < 0) {
    kprintf ("fatal: error reading binlog\n");
    exit (1);
  }
  binlog_load_time += mytime();
  binlog_loaded_size = log_readto_pos - jump_log_pos;
  if (!binlog_disabled) {
    clear_read_log();
  }
  clear_write_log ();
  start_time = time (0);

  start_server ();

  return 0;
}