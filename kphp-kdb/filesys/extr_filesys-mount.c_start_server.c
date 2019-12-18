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
 int active_connections ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cron () ; 
 int /*<<< orphan*/  ct_filesys_engine_server ; 
 int /*<<< orphan*/  epoll_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  epoll_pre_event () ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  ff_sfd ; 
 int /*<<< orphan*/  ff_stop_server ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int,int,int,int) ; 
 int /*<<< orphan*/  init_epoll () ; 
 int /*<<< orphan*/  init_listening_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_netbuffers () ; 
 int maxconn ; 
 int /*<<< orphan*/  memcache_methods ; 
 int now ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ verbosity ; 

__attribute__((used)) static void *start_server (void *arg) {
  int i, prev_time = 0;

  init_epoll ();
  init_netbuffers ();
  init_listening_connection (ff_sfd, &ct_filesys_engine_server, &memcache_methods);

  for (i = 0; !ff_stop_server ; i++) {
    if (verbosity > 0 && !(i & 255)) {
      fprintf (stderr, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (67);

    if (now != prev_time) {
      prev_time = now;
      cron ();
    }

    if (epoll_pre_event) {
      epoll_pre_event();
    }
  }

  epoll_close (ff_sfd);
  close (ff_sfd);
  pthread_exit (NULL);
}