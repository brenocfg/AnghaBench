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
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int active_connections ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 char* conv_addr (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  copyfast_rpc_server ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_rpc_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  epoll_close (scalar_t__) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int /*<<< orphan*/  interactive ; 
 int maxconn ; 
 int now ; 
 int port ; 
 scalar_t__ quit_steps ; 
 scalar_t__ server_socket (int,TYPE_1__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsid () ; 
 TYPE_1__ settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  stderr ; 
 char* username ; 
 scalar_t__ verbosity ; 

void start_server (void) { 
  //  struct sigaction sa;
  char buf[64];
  int i;
  int prev_time;

  init_epoll();
  init_netbuffers();

  prev_time = 0;

  if (!sfd) {
    sfd = server_socket (port, settings_addr, backlog, 0);
  }

  if (sfd < 0) {
    fprintf(stderr, "cannot open server socket at port %d: %m\n", port);
    exit(3);
  }

  if (verbosity) {
    fprintf (stderr, "created listening socket at %s:%d, fd=%d\n", conv_addr(settings_addr.s_addr, buf), port, sfd);
  }

  if (daemonize) {
    setsid();
  }

  if (change_user(username) < 0 && !interactive) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit(1);
  }

  init_listening_connection (sfd, &ct_rpc_server, &copyfast_rpc_server);
 
  signal(SIGINT, sigint_handler);
  signal(SIGTERM, sigterm_handler);
  signal(SIGUSR1, sigusr1_handler);
  if (daemonize) {
    signal(SIGHUP, sighup_handler);
  }
  signal(SIGPIPE, SIG_IGN);

  for (i = 0; ; i++) {
    if (verbosity > 0 && !(i & 255)) {
      fprintf (stderr, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (53);

    if (now != prev_time) {
      prev_time = now;
      cron();
    }
    if (quit_steps && !--quit_steps) break;
  }

  epoll_close (sfd);
  close(sfd);
}