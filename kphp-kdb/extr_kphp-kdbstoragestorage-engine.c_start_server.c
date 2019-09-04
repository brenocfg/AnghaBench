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
struct connection {int pending_queries; } ;
struct TYPE_3__ {int /*<<< orphan*/  volume_id; } ;

/* Variables and functions */
 struct connection* Connections ; 
 int /*<<< orphan*/  NB_alloc ; 
 int /*<<< orphan*/  NB_max ; 
 int /*<<< orphan*/  NB_used ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGPOLL ; 
 int /*<<< orphan*/  SIGRTMAX ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 TYPE_1__** Volumes ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/ * active_write_threads ; 
 int /*<<< orphan*/  append_to_binlog_time ; 
 int /*<<< orphan*/  binlog_disabled ; 
 int /*<<< orphan*/  booting_time ; 
 int /*<<< orphan*/  check_all_aio_completions () ; 
 int /*<<< orphan*/  close (scalar_t__) ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_http_server ; 
 int /*<<< orphan*/  ct_rpc_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  epoll_close (scalar_t__) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 scalar_t__ force_interrupt ; 
 int force_reopen_logs ; 
 int /*<<< orphan*/  forward_query_check_all_completions () ; 
 int /*<<< orphan*/  http_methods ; 
 scalar_t__ http_sfd ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int /*<<< orphan*/  kprintf (char*,...) ; 
 int /*<<< orphan*/  maxconn ; 
 int /*<<< orphan*/  mytime () ; 
 int now ; 
 int /*<<< orphan*/  reopen_logs () ; 
 int /*<<< orphan*/  save_index_process ; 
 int /*<<< orphan*/  setsid () ; 
 scalar_t__ sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sigpoll_cnt ; 
 int /*<<< orphan*/  sigpoll_handler ; 
 int /*<<< orphan*/  sigrtmax_handler ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  sleep (int) ; 
 int storage_append_to_binlog (TYPE_1__*) ; 
 int /*<<< orphan*/  storage_rpc_server ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  vkprintf (int,char*,scalar_t__,...) ; 
 int volumes ; 
 scalar_t__ write_thread_check_all_completions () ; 

void start_server (void) {
  int i;
  int prev_time;
  int old_reopen_logs = 0;

  init_epoll();
  init_netbuffers();

  prev_time = 0;

  if (daemonize) {
    setsid ();
    reopen_logs ();
  }

/*
  for (i = 0; i < volumes; i++) {
    storage_open_binlogs (Volumes[i]);
  }
*/
  append_to_binlog_time = -mytime ();
  if (!binlog_disabled) {
    for (i = 0; i < volumes; i++) {
      int r = storage_append_to_binlog (Volumes[i]);
      if (r < 0) {
        kprintf ("[v%lld] storage_append_to_binlog returns error code %d.\n", Volumes[i]->volume_id, r);
        exit (1);
      }
    }
  }
  append_to_binlog_time += mytime ();

  struct connection *c = &Connections[0];
  c->pending_queries = 0x7fffffff;

  init_listening_connection (sfd, &ct_rpc_server, &storage_rpc_server);

  if (http_sfd >= 0) {
    init_listening_connection (http_sfd, &ct_http_server, &http_methods);
  }

  signal (SIGINT, sigint_handler);
  signal (SIGTERM, sigterm_handler);
  signal (SIGUSR1, sigusr1_handler);
  signal (SIGPIPE, SIG_IGN);
  signal (SIGIO, SIG_IGN);
  signal (SIGPOLL, sigpoll_handler);
  signal (SIGRTMAX, sigrtmax_handler);
  if (daemonize) {
    signal (SIGHUP, sighup_handler);
  }

  int quit_steps = 0;

  booting_time += mytime ();

  for (i = 0; ; i++) {
    if (!(i & 255)) {
      vkprintf (1, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (57);

    if (force_interrupt) {
      if (!save_index_process) {
        kprintf ("Waiting write threads terminates.\n");
        int k = 0;
        while (active_write_threads != NULL) {
          sleep (1);
          k += write_thread_check_all_completions ();
        }
        kprintf ("%d threads has been terminated.\n", k);
        kprintf ("Start sync.\n");
        sync ();
        kprintf ("Sync has been completed.\n");
      }
      exit (0);
    }

    if (force_reopen_logs != old_reopen_logs) {
      old_reopen_logs = force_reopen_logs;
      kprintf ("reopen_logs (), force_reopen_logs counter is equal to %d.\n", old_reopen_logs);
      reopen_logs ();
    }

    if (sigpoll_cnt > 0) {
      vkprintf (2, "after epoll_work(), sigpoll_cnt=%d\n", sigpoll_cnt);
      sigpoll_cnt = 0;
    }

    /* !!! */
    check_all_aio_completions ();
    write_thread_check_all_completions ();
    forward_query_check_all_completions ();

    if (now != prev_time) {
      prev_time = now;
      cron();
    }
    if (quit_steps && !--quit_steps) break;
  }

  epoll_close (sfd);
  close (sfd);

}