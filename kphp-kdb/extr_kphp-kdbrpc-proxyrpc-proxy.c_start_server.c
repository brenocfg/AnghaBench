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
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ binlog_mode_on ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  create_all_outbound_connections () ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_rpc_server ; 
 int /*<<< orphan*/  ct_tcp_rpc_server ; 
 scalar_t__ daemonize ; 
 int default_udp_socket ; 
 int /*<<< orphan*/  do_reload_config (int) ; 
 double drand48 () ; 
 scalar_t__ enable_ipv6 ; 
 int /*<<< orphan*/  epoll_close (scalar_t__) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  flush_cbinlog (int) ; 
 int /*<<< orphan*/  flush_index () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  get_utime_monotonic () ; 
 int /*<<< orphan*/  init_epoll () ; 
 scalar_t__ init_listening_tcpv6_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  init_msg_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int init_udp_port (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  kprintf (char*,scalar_t__) ; 
 int maxconn ; 
 scalar_t__ need_reload_config ; 
 int now ; 
 scalar_t__ pending_signals ; 
 int port ; 
 double precise_now ; 
 scalar_t__ quit_steps ; 
 int /*<<< orphan*/  rpc_proxy_inbound ; 
 int /*<<< orphan*/  rpc_proxy_tcp ; 
 int /*<<< orphan*/  rpc_proxy_udp_server ; 
 int /*<<< orphan*/  rpc_proxy_udp_server_methods ; 
 scalar_t__ server_socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  sigusr2_handler ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tcp_buffers ; 
 char* username ; 
 scalar_t__ usfd ; 
 scalar_t__ verbosity ; 

void start_server (void) { 
  //  struct sigaction sa;
  int i;
  int prev_time;
  double next_create_outbound = 0;

  init_epoll();
  init_netbuffers();
  init_msg_buffers (0);

  prev_time = 0;

  if (daemonize) {
    setsid ();
  }

  if (change_user (username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }
  
  if (!sfd) {
    sfd = server_socket (port, settings_addr, backlog, enable_ipv6 );
  }

  if (sfd < 0) {
    fprintf (stderr, "cannot open server socket at port %d: %m\n", port);
    exit (1);
  }

  if (!usfd) {
    usfd = server_socket (port, settings_addr, backlog, enable_ipv6 + 1);
  }

  if (usfd < 0) {
    fprintf (stderr, "cannot open udp port: %m\n");
    exit (1);
  }

  if (!tcp_buffers) {
    assert (init_listening_tcpv6_connection (sfd, &ct_rpc_server, &rpc_proxy_inbound, enable_ipv6) >= 0);
  } else {
    assert (init_listening_tcpv6_connection (sfd, &ct_tcp_rpc_server, &rpc_proxy_tcp, enable_ipv6) >= 0);
  }
 
  assert ((default_udp_socket = init_udp_port (usfd, port, &rpc_proxy_udp_server, &rpc_proxy_udp_server_methods, enable_ipv6)));

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
      next_create_outbound = precise_now + 0.05 + 0.02 * drand48();
    }
    if (now != prev_time) {
      prev_time = now;
      cron ();
    }
    if (pending_signals) {
      break;
    }
    if (need_reload_config) {
      do_reload_config (1);
    }
    if (binlog_mode_on) {
      flush_cbinlog (0);
    }
    if (quit_steps && !--quit_steps) break;
  }
  
  epoll_close (sfd);
  close(sfd);

  if (binlog_mode_on) {
    flush_cbinlog (2);
    flush_index ();
  }
  kprintf ("Terminated (pending_signals = 0x%llx).\n", pending_signals);

}