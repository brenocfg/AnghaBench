#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 int NB_alloc ; 
 int NB_max ; 
 int NB_used ; 
 long long SIGHUP ; 
 long long SIGINT ; 
 long long SIGPIPE ; 
 long long SIGPOLL ; 
 long long SIGTERM ; 
 long long SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int active_connections ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backlog ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ change_user (char*) ; 
 scalar_t__ close (scalar_t__) ; 
 char* conv_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_rpc_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  epoll_close (scalar_t__) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flush_all (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int maxconn ; 
 int now ; 
 long long pending_signals ; 
 int port ; 
 scalar_t__ quit_steps ; 
 int /*<<< orphan*/  reopen_logs () ; 
 int /*<<< orphan*/  rpc_methods ; 
 scalar_t__ server_socket (int,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsid () ; 
 TYPE_1__ settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (long long,int /*<<< orphan*/ ) ; 
 int sigpoll_cnt ; 
 int /*<<< orphan*/  sigpoll_handler ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tl_restart_all_ready () ; 
 char* username ; 
 int verbosity ; 

void start_server (void) {
  int i;
  int prev_time;

  init_epoll();
  init_netbuffers();

  prev_time = 0;

  if (!sfd) {
    sfd = server_socket (port, settings_addr, backlog, 0);
  }

  if (sfd < 0) {
    fprintf (stderr, "cannot open server socket at port %d: %m\n", port);
    exit (3);
  }

  if (verbosity > 0) {
    fprintf (stderr, "created listening socket at %s:%d, fd=%d\n", conv_addr (settings_addr.s_addr, buf), port, sfd);
  }

  if (daemonize) {
    setsid();
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_listening_connection (sfd, &ct_rpc_server, &rpc_methods);

  signal (SIGINT, sigint_handler);
  signal (SIGTERM, sigterm_handler);
  signal (SIGUSR1, sigusr1_handler);
  signal (SIGPIPE, SIG_IGN);
  signal (SIGPOLL, sigpoll_handler);
  if (daemonize) {
    signal (SIGHUP, sighup_handler);
    reopen_logs();
  }

  if (verbosity > 0) {
    fprintf (stderr, "Server started\n");
  }

  for (i = 0; !(pending_signals & ~((1ll << SIGUSR1) | (1ll << SIGHUP))); i++) {
    if (verbosity > 0 && !(i & 255)) {
      fprintf (stderr, "epoll_work(): %d out of %d connections, network bufers: %d used, %d out of %d allocated\n",
         active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (57);

    if (sigpoll_cnt > 0) {
      if (verbosity > 1) {
        fprintf (stderr, "after epoll_work(), sigpoll_cnt=%d\n", sigpoll_cnt);
      }
      sigpoll_cnt = 0;
    }

    if (pending_signals & (1ll << SIGHUP)) {
      pending_signals &= ~(1ll << SIGHUP);

      flush_all (1);
    }

    if (pending_signals & (1ll << SIGUSR1)) {
      pending_signals &= ~(1ll << SIGUSR1);

      reopen_logs();
      flush_all (1);
    }

    tl_restart_all_ready();

    if (now != prev_time) {
      prev_time = now;
      cron();
    }

    if (quit_steps && !--quit_steps) break;
  }

  if (verbosity > 0 && pending_signals) {
    fprintf (stderr, "Quitting because of pending signals = %llx\n", pending_signals);
  }

  epoll_close (sfd);
  assert (close (sfd) >= 0);
}