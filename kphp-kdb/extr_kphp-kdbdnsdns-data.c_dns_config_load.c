#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lev_start {int split_mod; int split_max; scalar_t__ split_min; scalar_t__ extra_bytes; int /*<<< orphan*/  schema_id; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {int /*<<< orphan*/  replica_prefix; } ;
struct TYPE_9__ {TYPE_1__* info; } ;
struct TYPE_8__ {int /*<<< orphan*/ * filename; } ;

/* Variables and functions */
 TYPE_2__* Binlog ; 
 int /*<<< orphan*/  DNS_SCHEMA_V1 ; 
 int /*<<< orphan*/  LEV_START ; 
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int PATH_MAX ; 
 struct lev_start* alloca (int) ; 
 scalar_t__ append_to_binlog (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  binlog_allow_query_networks ; 
 int /*<<< orphan*/  binlog_allow_query_networks6 ; 
 int /*<<< orphan*/ * binlogname ; 
 int /*<<< orphan*/  clear_log () ; 
 int /*<<< orphan*/  clear_read_log () ; 
 int /*<<< orphan*/  clear_write_log () ; 
 scalar_t__ close (int) ; 
 int /*<<< orphan*/  close_binlog (TYPE_2__*,int) ; 
 int config_load (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_zones ; 
 int dns_convert_config_to_binlog ; 
 int /*<<< orphan*/  dns_record_hash_free () ; 
 int /*<<< orphan*/  dns_record_hash_init () ; 
 scalar_t__ engine_preload_filelist (char const*,int /*<<< orphan*/ *) ; 
 TYPE_3__* engine_replica ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  expand_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_binlog_last () ; 
 scalar_t__ fsync (int) ; 
 char const* include_binlog_name ; 
 int /*<<< orphan*/  init_log_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ log_readto_pos ; 
 int open (char*,int,int) ; 
 TYPE_2__* open_binlog (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ replay_log (int /*<<< orphan*/ ,int) ; 
 int snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  sync_binlog (int) ; 
 int /*<<< orphan*/  vkprintf (int,char*) ; 
 int write (int,struct lev_start*,int) ; 
 int /*<<< orphan*/  zones ; 

int dns_config_load (const char *filename, int exit_after_first_error, const char *output_binlog_name) {
  if (output_binlog_name) {
    char a[PATH_MAX];
    assert (snprintf (a, PATH_MAX, "%s.bin", output_binlog_name) < PATH_MAX);
    int fd = open (a, O_CREAT | O_WRONLY | O_EXCL, 0660);
    if (fd < 0) {
      kprintf ("open ('%s', O_CREAT | O_WRONLY | O_EXCL, 0660) failed. %m\n", a);
      exit (1);
    }
    struct lev_start *E = alloca (24);
    E->type = LEV_START;
    E->schema_id = DNS_SCHEMA_V1;
    E->extra_bytes = 0;
    E->split_mod = 1;
    E->split_min = 0;
    E->split_max = 1;
    assert (write (fd, E, 24) == 24);
    assert (fsync (fd) >= 0);
    assert (close (fd) >= 0);
    if (engine_preload_filelist (output_binlog_name, NULL) < 0) {
      kprintf ("cannot open binlog files for %s\n", output_binlog_name);
      exit (1);
    }
    Binlog = open_binlog (engine_replica, 0);
    if (!Binlog) {
      kprintf ("fatal: cannot find binlog for %s, log position %lld\n", engine_replica->replica_prefix, 0ll);
      exit (1);
    }
    binlogname = Binlog->info->filename;
    clear_log ();
    init_log_data (0, 0, 0);
    vkprintf (1, "replay log events started\n");
    assert (replay_log (0, 1) >= 0);
    vkprintf (1, "replay log events finished\n");
    clear_read_log();
    clear_write_log ();
    assert (append_to_binlog (Binlog) == log_readto_pos);
    dns_convert_config_to_binlog = 1;
  }
  include_binlog_name = NULL;
  dns_record_hash_init ();
  int res = config_load (filename, exit_after_first_error, 0);
  dns_record_hash_free ();
  expand_name (0); //free cyclic buffer
  config_zones = zones;
  if (output_binlog_name) {
    if (include_binlog_name) {
      kprintf ("ERROR: Config contains $BINLOG macro. This feature is forbidden in writing binlog mode.\n");
      return -1;
    }
    flush_binlog_last ();
    sync_binlog (2);
    close_binlog (Binlog, 1);
    Binlog = NULL;
    binlogname = NULL;
  }

  if (include_binlog_name && !binlog_allow_query_networks && !binlog_allow_query_networks6) {
    kprintf ("Ignore '$BINLOG %s' macro since there isn't any '$BINLOG_ALLOW_QUERY <network addr>' macro in config.\n", include_binlog_name);
    include_binlog_name = NULL;
  }
  return res;
}