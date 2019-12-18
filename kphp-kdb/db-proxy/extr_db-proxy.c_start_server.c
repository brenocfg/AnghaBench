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

/* Variables and functions */
 int NB_alloc ; 
 int NB_max ; 
 int NB_used ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int active_connections ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_memcache_server ; 
 int /*<<< orphan*/  ct_mysql_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  db_proxy_inbound ; 
 int /*<<< orphan*/  db_proxy_memcache_inbound ; 
 int /*<<< orphan*/  do_reload_config (int) ; 
 double drand48 () ; 
 int /*<<< orphan*/  epoll_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int maxconn ; 
 scalar_t__ memcache_port ; 
 int /*<<< orphan*/  memcache_sfd ; 
 scalar_t__ need_reload_config ; 
 int now ; 
 double precise_now ; 
 scalar_t__ quit_steps ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  sigusr2_handler ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  test_mode ; 
 char* username ; 
 scalar_t__ verbosity ; 

void start_server (void) { 
  //  struct sigaction sa;
  int i;
  int prev_time;
  double next_create_outbound = 0;

  init_epoll();
  init_netbuffers();

  prev_time = 0;

  if (daemonize) {
    setsid();
  }

  if (change_user (username) < 0 && !test_mode) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit(1);
  }

  init_listening_connection (sfd, &ct_mysql_server, &db_proxy_inbound);

  if (memcache_port) {
    init_listening_connection (memcache_sfd, &ct_memcache_server, &db_proxy_memcache_inbound);
  }

  create_all_outbound_connections ();

  signal(SIGINT, sigint_handler);
  signal(SIGTERM, sigterm_handler);
  signal(SIGUSR1, sigusr1_handler);
  signal(SIGUSR2, sigusr2_handler);
  signal(SIGPIPE, SIG_IGN);
  if (daemonize) {
    signal(SIGHUP, sighup_handler);
  }

  for (i = 0; ; i++) {
    if (verbosity > 0 && !(i & 255)) {
      fprintf (stderr, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (50);
    if (precise_now > next_create_outbound) {
      create_all_outbound_connections ();
      next_create_outbound = precise_now + 0.03 + 0.02 * drand48();
    }
    if (now != prev_time) {
      prev_time = now;
      cron();
    }
    if (need_reload_config) {
      do_reload_config (1);
    }
    if (quit_steps && !--quit_steps) break;
  }

  epoll_close (sfd);
  close(sfd);
  
  //  flush_binlog_ts();
}