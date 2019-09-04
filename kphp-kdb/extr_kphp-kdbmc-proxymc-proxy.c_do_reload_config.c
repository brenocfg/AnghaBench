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
struct mc_config {scalar_t__* config_md5_hex; int /*<<< orphan*/  config_bytes; scalar_t__ config_loaded_at; } ;

/* Variables and functions */
 struct mc_config* CurConf ; 
 struct mc_config* NextConf ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  clear_config (struct mc_config*,int) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  config_buff ; 
 int /*<<< orphan*/  config_bytes ; 
 char* config_filename ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__* fd ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int kdb_load_hosts () ; 
 int /*<<< orphan*/  md5_hex (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ need_reload_config ; 
 scalar_t__ now ; 
 scalar_t__ open (char*,int /*<<< orphan*/ ) ; 
 int parse_config (struct mc_config*,struct mc_config*,int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ time (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transfer_listening_sockets (struct mc_config*,struct mc_config*) ; 
 int try_open_new_listening_sockets (struct mc_config*) ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__* zmalloc (int) ; 

int do_reload_config (int create_conn) {
  int res;
  need_reload_config = 0;

  fd[0] = open (config_filename, O_RDONLY);
  if (fd[0] < 0) {
    fprintf (stderr, "cannot re-read config file %s: %m\n", config_filename);
    return -1;
  }

  res = kdb_load_hosts ();
  if (res > 0 && verbosity > 0) {
    fprintf (stderr, "/etc/hosts changed, reloaded\n");
  }

  res = parse_config (NextConf, CurConf, 0);

  close (fd[0]);

  //  clear_config (NextConf);
  
  if (res < 0) {
    vkprintf (0, "error while re-reading config file %s, new configuration NOT applied\n", config_filename);
    return res;
  }

  res = try_open_new_listening_sockets (NextConf);
  if (res < 0) {
    vkprintf (0, "error while re-reading config file %s, new configuration NOT applied: cannot open listening ports\n", config_filename);
    return res;
  }

  res = parse_config (NextConf, CurConf, 1);

  if (res < 0) {
    clear_config (NextConf, 0);
    vkprintf (0, "fatal error while re-reading config file %s\n", config_filename);
    exit (-res);
  }

  if (create_conn) {
    transfer_listening_sockets (NextConf, CurConf);
  }

  struct mc_config *tmp = CurConf;
  CurConf = NextConf;
  NextConf = tmp;

  clear_config (NextConf, 1);

  if (create_conn) {
    create_all_outbound_connections ();
  }

  CurConf->config_loaded_at = now ? now : time (0);
  CurConf->config_bytes = config_bytes;
  CurConf->config_md5_hex = zmalloc (33);
  md5_hex (config_buff, config_bytes, CurConf->config_md5_hex);
  CurConf->config_md5_hex[32] = 0;

  vkprintf (0, "configuration file %s re-read successfully, new configuration active\n", config_filename);

  return 0;
}