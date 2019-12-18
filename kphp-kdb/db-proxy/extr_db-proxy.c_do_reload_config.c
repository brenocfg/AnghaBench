#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  db_hash_table_p ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  clear_db_hash_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 char* config_filename ; 
 int /*<<< orphan*/  config_reload_time ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  db_hash ; 
 int /*<<< orphan*/  db_hash_new ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int kdb_load_hosts () ; 
 scalar_t__ need_reload_config ; 
 int /*<<< orphan*/  now ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int parse_config (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

int do_reload_config (int create_conn) {
  int res;
  need_reload_config = 0;

  fd[0] = open (config_filename, O_RDONLY);
  if (fd[0] < 0) {
    fprintf (stderr, "cannot re-read config file %s: %m\n", config_filename);
    return -3;
  }

  res = kdb_load_hosts ();
  if (res > 0 && verbosity > 0) {
    fprintf (stderr, "/etc/hosts changed, reloaded\n");
  }

  res = parse_config (db_hash_new, 4);

  close (fd[0]);

  if (res < 0) {
    clear_db_hash_table (db_hash_new);
    fprintf (stderr, "error while re-reading config file %s, new configuration NOT applied\n", config_filename);
    return res;
  }

  res = parse_config (db_hash_new, 3);

  if (res < 0) {
    clear_db_hash_table (db_hash_new);
    fprintf (stderr, "error while re-reading config file %s, new configuration NOT applied\n", config_filename);
    return res;
  }

  res = parse_config (db_hash_new, 1);

  if (res < 0) {
    clear_db_hash_table (db_hash_new);
    fprintf (stderr, "fatal error while re-reading config file %s\n", config_filename);
    exit (-res);
  }

  clear_db_hash_table (db_hash);

  db_hash_table_p tmp = db_hash;
  db_hash = db_hash_new;
  db_hash_new = tmp;

  if (create_conn) {
    create_all_outbound_connections ();
  }

  config_reload_time = now;

  if (verbosity > 0) {
    fprintf (stderr, "configuration file %s re-read successfully, new configuration active\n", config_filename);
  }

  return 0;
}