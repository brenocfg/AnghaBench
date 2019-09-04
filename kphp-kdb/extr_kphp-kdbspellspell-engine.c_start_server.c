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
 int /*<<< orphan*/  NB_alloc ; 
 int /*<<< orphan*/  NB_max ; 
 int /*<<< orphan*/  NB_used ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGIO ; 
 int /*<<< orphan*/  SIGPIPE ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  active_connections ; 
 scalar_t__ change_user (char*) ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_spell_engine_server ; 
 scalar_t__ daemonize ; 
 int /*<<< orphan*/  epoll_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int /*<<< orphan*/  maxconn ; 
 int /*<<< orphan*/  memcache_methods ; 
 int now ; 
 int /*<<< orphan*/  setsid () ; 
 int /*<<< orphan*/  sfd ; 
 int /*<<< orphan*/  sighup_handler ; 
 int /*<<< orphan*/  sigint_handler ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sigterm_handler ; 
 int /*<<< orphan*/  sigusr1_handler ; 
 int /*<<< orphan*/  stderr ; 
 char* username ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void start_server (void) {
  int i;
  int prev_time;

  init_epoll ();
  init_netbuffers ();

  prev_time = 0;

  if (daemonize) {
    setsid();
  }

  if (change_user(username) < 0) {
    fprintf (stderr, "fatal: cannot change user to %s\n", username ? username : "(none)");
    exit (1);
  }

  init_listening_connection (sfd, &ct_spell_engine_server, &memcache_methods);

  signal (SIGINT, sigint_handler);
  signal (SIGTERM, sigterm_handler);
  signal (SIGUSR1, sigusr1_handler);
  signal (SIGPIPE, SIG_IGN);
  signal (SIGIO, SIG_IGN);
  if (daemonize) {
    signal (SIGHUP, sighup_handler);
  }

  int quit_steps = 0;

  for (i = 0; ; i++) {
    if (!(i & 255)) {
      vkprintf (1, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (57);

    if (now != prev_time) {
      prev_time = now;
      cron();
    }
    if (quit_steps && !--quit_steps) break;
  }

  epoll_close (sfd);
  close (sfd);

}