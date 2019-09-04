#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_6__ {scalar_t__ cron; scalar_t__ save_index; scalar_t__ sigusr1; scalar_t__ sighup; } ;
typedef  TYPE_1__ server_functions_t ;
typedef  int /*<<< orphan*/  sa ;
struct TYPE_7__ {scalar_t__ sfd; int /*<<< orphan*/  settings_addr; } ;
typedef  TYPE_2__ engine_t ;
typedef  int /*<<< orphan*/  conn_type_t ;
struct TYPE_8__ {scalar_t__ cron; scalar_t__ save_index; scalar_t__ sigusr1; scalar_t__ sighup; } ;

/* Variables and functions */
 int /*<<< orphan*/  Binlog ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGPOLL ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  add_udp_socket (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ append_to_binlog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  backlog ; 
 scalar_t__ binlog_disabled ; 
 scalar_t__ binlog_fd ; 
 scalar_t__ binlogname ; 
 scalar_t__ change_user (char*) ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  epoll_pre_event ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (scalar_t__,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  init_msg_buffers (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int /*<<< orphan*/  kprintf (char*,char*) ; 
 scalar_t__ log_readto_pos ; 
 int /*<<< orphan*/  memset (struct sigaction*,int /*<<< orphan*/ ,int) ; 
 char* port ; 
 int /*<<< orphan*/  read_new_events ; 
 int /*<<< orphan*/  reopen_logs () ; 
 scalar_t__ server_socket (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsid () ; 
 TYPE_3__ sf ; 
 int /*<<< orphan*/  sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  sigterm_handler ; 
 scalar_t__ udp_enabled ; 
 char* username ; 

void server_init (engine_t *E, server_functions_t *F, conn_type_t *listen_connection_type, void *listen_connection_extra) {
  if (F != NULL) {
    if (F->sighup) {
      sf.sighup = F->sighup;
    }
    if (F->sigusr1) {
      sf.sigusr1 = F->sigusr1;
    }
    if (F->save_index) {
      sf.save_index = F->save_index;
    }
    if (F->cron) {
      sf.cron = F->cron;
    }
  }
  
  init_epoll ();
  init_netbuffers ();
  if (udp_enabled) {
    init_msg_buffers (0);
  }
  
  if (daemonize) {
    setsid ();
    reopen_logs ();
  }

  if (!E->sfd) {
    E->sfd = server_socket (port, E->settings_addr, backlog, 0);
  }

  if (E->sfd < 0) {
    kprintf ("cannot open server socket at port %d: %m\n", port);
    exit (1);
  }

  if (change_user (username) < 0) {
    kprintf ("fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  if (binlogname && !binlog_disabled) {
    assert (append_to_binlog (Binlog) == log_readto_pos);
  }

  init_listening_connection (E->sfd, listen_connection_type, listen_connection_extra);
  if (udp_enabled) {
    add_udp_socket (port, 0);
  }
  
  if (binlog_disabled && binlog_fd >= 0) {
    epoll_pre_event = read_new_events;
  }

  struct sigaction sa;
  memset (&sa, 0, sizeof (sa));
  sa.sa_handler = sigint_handler;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGTERM); 
  sigaction (SIGINT, &sa, NULL);
  
  sa.sa_handler = sigterm_handler;
  sigemptyset (&sa.sa_mask);
  sigaddset (&sa.sa_mask, SIGINT);
  sigaction (SIGTERM, &sa, NULL);
  
  sa.sa_handler = SIG_IGN;
  sigaction (SIGPIPE, &sa, NULL);
  sigaction (SIGPOLL, &sa, NULL);
  
  if (daemonize) {
    sa.sa_handler = sighup_handler;
    sigemptyset (&sa.sa_mask);
    sigaction (SIGHUP, &sa, NULL);
  }
}