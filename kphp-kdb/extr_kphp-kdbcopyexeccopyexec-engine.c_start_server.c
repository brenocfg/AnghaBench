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
struct sigaction {int /*<<< orphan*/  sa_flags; int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;

/* Variables and functions */
 int /*<<< orphan*/  Binlog ; 
 long long FullVersionStr ; 
 int /*<<< orphan*/  NB_alloc ; 
 int /*<<< orphan*/  NB_max ; 
 int /*<<< orphan*/  NB_used ; 
 int /*<<< orphan*/  SA_NOCLDSTOP ; 
 long long SIGCHLD ; 
 long long SIGHUP ; 
 long long SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int SIGRTMAX ; 
 long long SIGTERM ; 
 long long SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  active_connections ; 
 scalar_t__ append_to_binlog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backlog ; 
 int /*<<< orphan*/  binlog_disabled ; 
 scalar_t__ binlogname ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  copyexec_aux_binlog_seek () ; 
 int /*<<< orphan*/  copyexec_main_sig_handler ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_copyexec_engine_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  epoll_close (scalar_t__) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int find_running_transactions () ; 
 int /*<<< orphan*/  flush_binlog_last () ; 
 scalar_t__ get_process_creation_time (scalar_t__) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 scalar_t__ interrupted_by_signal () ; 
 int /*<<< orphan*/  kill (scalar_t__,long long) ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 scalar_t__ log_readto_pos ; 
 int /*<<< orphan*/  maxconn ; 
 int /*<<< orphan*/  memcache_methods ; 
 int now ; 
 long long pending_signals ; 
 int /*<<< orphan*/  pending_signals_clear_bit (int /*<<< orphan*/ *,long long) ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  reopen_logs () ; 
 scalar_t__ results_client_creation_time ; 
 scalar_t__ results_client_pid ; 
 scalar_t__ server_socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  settings_addr ; 
 scalar_t__ sfd ; 
 scalar_t__ sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,long long) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_binlog (int) ; 
 int /*<<< orphan*/  transaction_auto_kill (long long) ; 
 int /*<<< orphan*/  transaction_check_child_status () ; 
 int /*<<< orphan*/  transaction_child_kill (long long) ; 
 int /*<<< orphan*/  vkprintf (int,char*,long long,...) ; 

void start_server (void) {
  int i, prev_time = 0;

  init_epoll ();

  if (!sfd && port >= 0) {
    sfd = server_socket (port, settings_addr, backlog, 0);
    if (sfd < 0) {
      kprintf ("cannot open server socket at port %d: %m\n", port);
      exit (3);
    }
    init_netbuffers ();
  }

  if (daemonize) {
    setsid ();
    reopen_logs ();
  }

  vkprintf (1, "%s\n", FullVersionStr);

  if (binlogname && !binlog_disabled) {
    vkprintf (3, "log_readto_pos: %lld\n", log_readto_pos);
    assert (append_to_binlog (Binlog) == log_readto_pos);
  }

  i = find_running_transactions ();
  vkprintf (1, "found %d running transactions\n", i);

  copyexec_aux_binlog_seek ();

  if (sfd) {
    init_listening_connection (sfd, &ct_copyexec_engine_server, &memcache_methods);
  }

  signal (SIGPIPE, SIG_IGN);
  signal (SIGIO, SIG_IGN);

  sigset_t signal_set;
  sigemptyset (&signal_set);
  sigaddset (&signal_set, SIGINT);
  sigaddset (&signal_set, SIGTERM);
  sigaddset (&signal_set, SIGUSR1);
  sigaddset (&signal_set, SIGCHLD);
  if (daemonize) {
    sigaddset (&signal_set, SIGHUP);
  }
  struct sigaction act;
  act.sa_handler = copyexec_main_sig_handler;
  act.sa_mask = signal_set;
  act.sa_flags = SA_NOCLDSTOP;
  for (i = 1; i <= SIGRTMAX; i++) {
    if (sigismember (&signal_set, i)) {
      if (sigaction (i, &act, NULL) < 0) {
        kprintf ("sigaction (%d) failed. %m\n", i);
        exit (1);
      }
    }
  }

  int quit_steps = 0;

  for (i = 0; ; i++) {
    if (!(i & 1023)) {
      vkprintf (2, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (77);

    if (interrupted_by_signal ()) {
      break;
    }

    if (pending_signals & (1LL << SIGCHLD)) {
      pending_signals_clear_bit (&signal_set, SIGCHLD);
      kprintf ("got SIGCHLD.\n");
      transaction_check_child_status ();
    }

    if (pending_signals & (1LL << SIGHUP)) {
      pending_signals_clear_bit (&signal_set, SIGHUP);
      kprintf ("got SIGHUP.\n");
      sync_binlog (2);
    }

    if (pending_signals & (1LL << SIGUSR1)) {
      pending_signals_clear_bit (&signal_set, SIGUSR1);
      kprintf ("got SIGUSR1, rotate logs.\n");
      reopen_logs ();
      transaction_child_kill (SIGUSR1);
      transaction_auto_kill (SIGUSR1);
      if (results_client_pid && results_client_creation_time && results_client_creation_time == get_process_creation_time (results_client_pid)) {
        kill (results_client_pid, SIGUSR1);
      }

      sync_binlog (2);
    }

    if (now != prev_time) {
      prev_time = now;
      cron ();
    }

    if (quit_steps && !--quit_steps) break;
  }

  if (sfd) {
    epoll_close (sfd);
    close (sfd);
  }

  flush_binlog_last ();
  sync_binlog (2);
  vkprintf (0, "Main process terminated (pending_signals: 0x%llx).\n", pending_signals);
}