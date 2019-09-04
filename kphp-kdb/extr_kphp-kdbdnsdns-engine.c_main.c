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
struct TYPE_6__ {int /*<<< orphan*/  filename; } ;

/* Variables and functions */
 TYPE_2__* Binlog ; 
 scalar_t__ PRIVILEGED_TCP_PORTS ; 
 int binlog_disabled ; 
 int /*<<< orphan*/  binlog_load_time ; 
 int /*<<< orphan*/  binlogname ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 char* config_name ; 
 scalar_t__ dns_config_load (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dns_reset () ; 
 int dynamic_data_buffer_size ; 
 scalar_t__ engine_preload_filelist (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* engine_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  f_parse_option ; 
 int /*<<< orphan*/  include_binlog_name ; 
 int /*<<< orphan*/  init_dyn_data () ; 
 int /*<<< orphan*/  init_log_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_msg_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jump_log_pos ; 
 int /*<<< orphan*/  keep_going ; 
 int /*<<< orphan*/  kprintf (char*,char*,...) ; 
 scalar_t__ maxconn ; 
 int /*<<< orphan*/  mytime () ; 
 int /*<<< orphan*/  no_argument ; 
 TYPE_2__* open_binlog (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  open_server_sockets () ; 
 size_t optind ; 
 int /*<<< orphan*/ * output_binlog_name ; 
 int /*<<< orphan*/  parse_engine_options_long (int,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_option (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char,char*) ; 
 scalar_t__ port ; 
 char* progname ; 
 scalar_t__ raise_file_rlimit (scalar_t__) ; 
 int /*<<< orphan*/  remove_parse_option (int) ; 
 scalar_t__ replay_log (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  required_argument ; 
 int /*<<< orphan*/  signals_init () ; 
 int /*<<< orphan*/  srand48 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_server () ; 
 int /*<<< orphan*/  start_time ; 
 scalar_t__ stats_port ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usage () ; 
 char* username ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 

int main (int argc, char *argv[]) {
  signals_init ();
  progname = argv[0];

  remove_parse_option ('r');
  remove_parse_option ('B');
  remove_parse_option (203);
  parse_option ("workers", required_argument, 0, 'M', "sets number of additional worker processes");
  parse_option ("max-response-records", required_argument, 0, 'R', "limits max records number in the response");
  parse_option ("stats-port", required_argument, 0, 'P', "sets port for getting stats using memcache queries");
  parse_option ("output", required_argument, 0, 'E', "sets exported binlog name for converting config to binlog");
  parse_option ("keep-going", no_argument, 0, 'k', "reports as much config errors as possible");
  parse_engine_options_long (argc, argv, f_parse_option);

  if (output_binlog_name) {
    port = stats_port = 0;
  }
  if (!port && output_binlog_name == NULL) {
    usage ();
  }
  config_name = argv[optind];

  if (port > 0 && port < PRIVILEGED_TCP_PORTS) {
    open_server_sockets ();
  }

  if (raise_file_rlimit (maxconn + 16) < 0) {
    kprintf ("fatal: cannot raise open file limit to %d\n", maxconn + 16);
    exit (1);
  }

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  srand48 (time (0));
  dynamic_data_buffer_size = 64 << 20;
  init_dyn_data ();
  dns_reset ();
  //TODO: replace config by binlog
  if (dns_config_load (config_name, !keep_going, output_binlog_name) < 0) {
    exit (1);
  }
  if (output_binlog_name) {
    exit (0);
  }
  if (include_binlog_name) {
    binlog_load_time = -mytime ();
    binlog_disabled = 1;
    if (engine_preload_filelist (include_binlog_name, NULL) < 0) {
      kprintf ("cannot open binlog files for %s\n", include_binlog_name);
      exit (1);
    }
    Binlog = open_binlog (engine_replica, jump_log_pos);
    if (!Binlog) {
      kprintf ("fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, jump_log_pos);
      exit (1);
    }
    binlogname = Binlog->info->filename;
    clear_log ();
    init_log_data (jump_log_pos, 0, 0);
    vkprintf (1, "replay log events started\n");
    if (replay_log (0, 1) < 0) {
      exit (1);
    }
    vkprintf (1, "replay log events finished\n");
    binlog_load_time += mytime ();
    if (!binlog_disabled) {
      clear_read_log ();
    }
    clear_write_log ();
  }
  init_msg_buffers (0);
  start_time = time (NULL);
  start_server ();
  return 0;
}