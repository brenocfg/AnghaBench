#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct in_addr {int dummy; } ;
struct hostent {scalar_t__ h_addrtype; int h_length; scalar_t__ h_addr; int /*<<< orphan*/  h_addr_list; } ;
struct TYPE_6__ {int /*<<< orphan*/  port; struct in_addr target; } ;
struct TYPE_5__ {int /*<<< orphan*/  s_addr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 int NB_alloc ; 
 int NB_max ; 
 int NB_used ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGPOLL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int active_connections ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backlog ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ change_user (char*) ; 
 scalar_t__ close (scalar_t__) ; 
 char* conv_addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  create_target (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_watchcat_engine_server ; 
 scalar_t__ daemonize ; 
 TYPE_3__ default_ct ; 
 int /*<<< orphan*/  epoll_close (scalar_t__) ; 
 int /*<<< orphan*/  epoll_pre_event () ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 struct hostent* gethostbyname (char*) ; 
 char* hostname ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int maxconn ; 
 int /*<<< orphan*/  memcache_methods ; 
 int now ; 
 int port ; 
 int /*<<< orphan*/  queue_conn ; 
 int /*<<< orphan*/  queue_port ; 
 scalar_t__ quit_steps ; 
 int /*<<< orphan*/  reopen_logs () ; 
 scalar_t__ server_socket (int,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsid () ; 
 TYPE_1__ settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int sigpoll_cnt ; 
 int /*<<< orphan*/  sigpoll_handler ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  stderr ; 
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

  if (verbosity) {
    fprintf (stderr, "created listening socket at %s:%d, fd=%d\n", conv_addr (settings_addr.s_addr, buf), port, sfd);
  }

  if (daemonize) {
    setsid();
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_listening_connection (sfd, &ct_watchcat_engine_server, &memcache_methods);

  struct hostent *h;
  if (!(h = gethostbyname (hostname)) || h->h_addrtype != AF_INET || h->h_length != 4 || !h->h_addr_list || !h->h_addr) {
    fprintf (stderr, "fatal: cannot resolve hostname %s: %m\n", hostname);
    exit (1);
  }

  default_ct.target = *(struct in_addr *) h->h_addr;
  default_ct.port = queue_port;
  queue_conn = create_target (&default_ct, 0);

  create_all_outbound_connections();

  signal (SIGINT, sigint_handler);
  signal (SIGTERM, sigterm_handler);
  signal (SIGUSR1, sigusr1_handler);
  signal (SIGPIPE, SIG_IGN);
  signal (SIGPOLL, sigpoll_handler);
  if (daemonize) {
    signal (SIGHUP, sighup_handler);
    reopen_logs();
  }

  if (verbosity) {
    fprintf (stderr, "Server started\n");
  }

  for (i = 0; ; i++) {
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

    if (now != prev_time) {
      prev_time = now;
      cron();
    }

    if (epoll_pre_event) {
      epoll_pre_event();
    }

    if (quit_steps && !--quit_steps) break;
  }

  fprintf (stderr, "Quitting.\n");

  epoll_close (sfd);
  assert (close (sfd) >= 0);
}