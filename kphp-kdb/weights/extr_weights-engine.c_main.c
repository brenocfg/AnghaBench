#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  replica_prefix; } ;
struct TYPE_12__ {TYPE_2__* info; } ;
struct TYPE_11__ {TYPE_1__* info; } ;
struct TYPE_10__ {char* filename; int /*<<< orphan*/  file_size; } ;
struct TYPE_9__ {scalar_t__ file_size; int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 TYPE_4__* Binlog ; 
 TYPE_3__* Snapshot ; 
 int /*<<< orphan*/  aes_pwd_file ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  binlog_load_time ; 
 char* binlogname ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 int /*<<< orphan*/  engine_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_5__* engine_replica ; 
 int /*<<< orphan*/ * engine_snapshot_name ; 
 int /*<<< orphan*/  engine_snapshot_replica ; 
 scalar_t__ engine_snapshot_size ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  index_load_time ; 
 scalar_t__ index_mode ; 
 int /*<<< orphan*/  init_log_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int load_index () ; 
 int /*<<< orphan*/  mytime () ; 
 int /*<<< orphan*/  no_argument ; 
 TYPE_4__* open_binlog (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* open_recent_snapshot (int /*<<< orphan*/ ) ; 
 int optind ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char,char*) ; 
 char* progname ; 
 int /*<<< orphan*/  remove_parse_option (int) ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  save_index (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_debug_handlers () ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 
 int /*<<< orphan*/  weights_engine ; 

int main (int argc, char *argv[]) {
  int i;
  set_debug_handlers ();
  parse_option ("index", no_argument, 0, 'i', "reindex");
  remove_parse_option (201);
  parse_option ("udp", no_argument, 0, 'U', "enables udp message support");
  parse_engine_options_long (argc, argv, f_parse_option);

  progname = argv[0];

  if (argc != optind + 1) {
    usage();
    return 2;
  }

  engine_init (&weights_engine, aes_pwd_file, index_mode);

  if (engine_preload_filelist (argv[optind], binlogname) < 0) {
    kprintf ("cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }

  vkprintf (3, "engine_preload_filelist done\n");

  //Snapshot reading
  Snapshot = open_recent_snapshot (engine_snapshot_replica);

  if (Snapshot) {
    engine_snapshot_name = strdup (Snapshot->info->filename);
    engine_snapshot_size = Snapshot->info->file_size;
    vkprintf (1, "load index file %s (size %lld)\n", engine_snapshot_name, engine_snapshot_size);

    index_load_time = -mytime();

    i = load_index ();

    if (i < 0) {
      kprintf ("load_index returned fail code %d.\n", i);
      exit (1);
    }
    index_load_time += mytime();
  } else {
    engine_snapshot_name = NULL;
    engine_snapshot_size = 0;
    index_load_time = 0;
  }

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

  binlog_load_time += mytime();

  if (!binlog_disabled) {
    clear_read_log();
  }

  if (i < 0) {
    kprintf ("fatal: error reading binlog\n");
    exit (1);
  }

  clear_write_log ();
  start_time = time (0);

  if (index_mode) {
    save_index (0);
  } else {
    start_server ();
  }

  return 0;
}