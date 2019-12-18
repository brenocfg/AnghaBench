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
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  ct_rpc_server ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  maxconn ; 
 int /*<<< orphan*/  process_signals () ; 
 int /*<<< orphan*/  rpc_methods ; 
 int /*<<< orphan*/  searchy_engine ; 
 int /*<<< orphan*/  searchy_functions ; 
 int /*<<< orphan*/  searchy_parse_function ; 
 int /*<<< orphan*/  searchy_stats ; 
 int /*<<< orphan*/  server_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double tl_aio_timeout ; 
 int /*<<< orphan*/  tl_parse_function ; 
 int /*<<< orphan*/  tl_restart_all_ready () ; 
 int /*<<< orphan*/  tl_stat_function ; 
 int verbosity ; 

void start_server (void) {
  int i;

  tl_parse_function = searchy_parse_function;
  tl_stat_function = searchy_stats;
  tl_aio_timeout = 2.0;

  server_init (&searchy_engine, &searchy_functions, &ct_rpc_server, &rpc_methods);

  int quit_steps = 0;

  for (i = 0; ; i++) {
    if (verbosity > 1 && !(i & 255)) {
      kprintf ("epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }

    epoll_work (57);
    if (!process_signals ()) {
      break;
    }
    tl_restart_all_ready ();
    if (quit_steps && !--quit_steps) break;
  }

  server_exit (&searchy_engine);
}