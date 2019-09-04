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
 int /*<<< orphan*/  PASSWORD_LENGTH ; 
 int /*<<< orphan*/  active_connections ; 
 int /*<<< orphan*/  ct_rpc_server ; 
 int /*<<< orphan*/  epoll_work (int) ; 
 int /*<<< orphan*/  maxconn ; 
 int /*<<< orphan*/  password_filename ; 
 int /*<<< orphan*/  process_signals () ; 
 int /*<<< orphan*/  random_engine ; 
 int /*<<< orphan*/  random_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random_functions ; 
 int /*<<< orphan*/  random_parse_function ; 
 int /*<<< orphan*/  random_stats ; 
 int /*<<< orphan*/  random_work (int) ; 
 int /*<<< orphan*/  rpc_methods ; 
 int /*<<< orphan*/  server_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 double tl_aio_timeout ; 
 int /*<<< orphan*/  tl_parse_function ; 
 int /*<<< orphan*/  tl_stat_function ; 
 int /*<<< orphan*/  vkprintf (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void start_server (void) {
  int i;

  tl_parse_function = random_parse_function;
  tl_stat_function = random_stats;
  tl_aio_timeout = 2.0;

  server_init (&random_engine, &random_functions, &ct_rpc_server, &rpc_methods);

  int quit_steps = 0;

  for (i = 0; ; i++) {
    if (!(i & 255)) {
      vkprintf (1, "epoll_work(): %d out of %d connections, network buffers: %d used, %d out of %d allocated\n",
	       active_connections, maxconn, NB_used, NB_alloc, NB_max);
    }
    epoll_work (7);
    random_work (80000 / (1000 / 11));
    if (!process_signals ()) {
      break;
    }
    if (quit_steps && !--quit_steps) break;
  }

  random_free (password_filename, PASSWORD_LENGTH);
  server_exit (&random_engine);
}