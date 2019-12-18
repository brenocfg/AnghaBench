#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int clusters_num; TYPE_1__* Clusters; } ;
struct TYPE_3__ {scalar_t__ server_socket; scalar_t__ listening_connection; int /*<<< orphan*/  mc_proxy_inbound; } ;

/* Variables and functions */
 scalar_t__ Connections ; 
 TYPE_2__* CurConf ; 
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
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_memcache_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  do_reload_config (int) ; 
 double drand48 () ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_utime_monotonic () ; 
 int /*<<< orphan*/  init_epoll () ; 
 scalar_t__ init_listening_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int maxconn ; 
 scalar_t__ need_reload_config ; 
 int now ; 
 double ping_interval ; 
 double precise_now ; 
 scalar_t__ quit_steps ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  sigusr2_handler ; 
 int /*<<< orphan*/  stderr ; 
 char* username ; 
 scalar_t__ verbosity ; 
 int /*<<< orphan*/  vkprintf (int /*<<< orphan*/ ,char*) ; 

void start_server (void) { 
  //  struct sigaction sa;
  int i;
  int prev_time;
  double next_create_outbound = 0;

  init_epoll();
  init_netbuffers();

  prev_time = 0;
  ping_interval *= 0.95 + 0.1 * drand48 ();

  if (daemonize) {
    setsid ();
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  for (i = 0; i < CurConf->clusters_num; i++) {
    assert (init_listening_connection (CurConf->Clusters[i].server_socket, &ct_memcache_server, &CurConf->Clusters[i].mc_proxy_inbound) >= 0);
    CurConf->Clusters[i].listening_connection = Connections + CurConf->Clusters[i].server_socket;
  }

  get_utime_monotonic ();

  create_all_outbound_connections ();

  signal (SIGINT, sigint_handler);
  signal (SIGTERM, sigterm_handler);
  signal (SIGUSR1, sigusr1_handler);
  signal (SIGUSR2, sigusr2_handler);
  signal (SIGPIPE, SIG_IGN);
  if (daemonize) {
    signal (SIGHUP, sighup_handler);
  }

  for (i = 0; ; i++) {
    if (verbosity > 0 && !(i & 255)) {
      fprintf (stderr, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
         active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (57);
    if (precise_now > next_create_outbound) {
      create_all_outbound_connections ();
      next_create_outbound = precise_now + 0.05 + 0.02 * drand48 ();
    }
    if (now != prev_time) {
      prev_time = now;
      cron ();
    }
    if (need_reload_config) {
#ifdef SEARCH_MODE_ENABLED
      vkprintf (0, "error: cannot reload configuration in mc-proxy-search mode\n");
      need_reload_config = 0;
#else
      do_reload_config (1);
#endif
    }
    if (quit_steps && !--quit_steps) break;
  }

}