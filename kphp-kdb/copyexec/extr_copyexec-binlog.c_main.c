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
 TYPE_2__* Binlog ; 
 void* atoi (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binlog_load_time ; 
 scalar_t__ binlog_loaded_size ; 
 char* binlogname ; 
 int /*<<< orphan*/  clear_log () ; 
 int dump_log_pos ; 
 int dump_timestamp ; 
 int dumping_crc32 ; 
 void* end_time ; 
 scalar_t__ engine_preload_filelist (char*,char*) ; 
 TYPE_3__* engine_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char*) ; 
 int /*<<< orphan*/  init_log_data (long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_crc32 ; 
 int /*<<< orphan*/  jump_log_ts ; 
 int /*<<< orphan*/  kprintf (char*,char*,...) ; 
 scalar_t__ log_readto_pos ; 
 int /*<<< orphan*/  mytime () ; 
 TYPE_2__* open_binlog (TYPE_3__*,long long) ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  out ; 
 int replay_log (int /*<<< orphan*/ ,int) ; 
 void* start_time ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  verbosity ; 
 int /*<<< orphan*/  vkprintf (int,char*,...) ; 

int main (int argc, char *argv[]) {
  int i;
  long long jump_log_pos = 0;
  out = stdout;
  while ((i = getopt (argc, argv, "tphvCS:T:")) != -1) {
    switch (i) {
    case 'C':
      dumping_crc32 = 1;
      break;
    case 'S':
      start_time = atoi (optarg);
      break;
    case 'T':
      end_time = atoi (optarg);
      break;
    case 'p':
      dump_log_pos = 1;
      break;
    case 't':
      dump_timestamp = 1;
      break;
    case 'v':
      verbosity++;
      break;
    case 'h':
      usage ();
    }
  }

  if (optind >= argc) {
    usage ();
  }

  if (engine_preload_filelist (argv[optind], binlogname) < 0) {
    kprintf ("cannot open binlog files for %s\n", binlogname ? binlogname : argv[optind]);
    exit (1);
  }

  vkprintf (3, "engine_preload_filelist done\n");

  Binlog = open_binlog (engine_replica, jump_log_pos);
  if (!Binlog) {
    kprintf ("fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, jump_log_pos);
    exit (1);
  }

  binlogname = Binlog->info->filename;

  vkprintf (1, "replaying binlog file %s (size %lld)\n", binlogname, Binlog->info->file_size);

  binlog_load_time = -mytime();
  clear_log();
  init_log_data (jump_log_pos, jump_log_ts, jump_log_crc32);
  vkprintf (1, "replay log events started\n");

  i = replay_log (0, 1);

  fflush (out);
  fclose (out);

  vkprintf (1, "replay log events finished\n");

  binlog_load_time += mytime();
  binlog_loaded_size = log_readto_pos - jump_log_pos;

  return 0;
}