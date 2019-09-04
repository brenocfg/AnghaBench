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
typedef  int /*<<< orphan*/  uv_timer_t ;
typedef  int /*<<< orphan*/  uv_handle_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ TCP ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,double) ; 
 double gbit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  loop ; 
 scalar_t__ nrecv ; 
 scalar_t__ nsent ; 
 int /*<<< orphan*/  nsent_total ; 
 int /*<<< orphan*/ * pipe_write_handles ; 
 scalar_t__ start_time ; 
 int /*<<< orphan*/  stats_left ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * tcp_write_handles ; 
 scalar_t__ type ; 
 int /*<<< orphan*/  uv_close (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ uv_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ ) ; 
 int write_sockets ; 

__attribute__((used)) static void show_stats(uv_timer_t* handle) {
  int64_t diff;
  int i;

#if PRINT_STATS
  fprintf(stderr, "connections: %d, write: %.1f gbit/s\n",
          write_sockets,
          gbit(nsent, STATS_INTERVAL));
  fflush(stderr);
#endif

  /* Exit if the show is over */
  if (!--stats_left) {

    uv_update_time(loop);
    diff = uv_now(loop) - start_time;

    fprintf(stderr, "%s_pump%d_client: %.1f gbit/s\n",
            type == TCP ? "tcp" : "pipe",
            write_sockets,
            gbit(nsent_total, diff));
    fflush(stderr);

    for (i = 0; i < write_sockets; i++) {
      if (type == TCP)
        uv_close((uv_handle_t*) &tcp_write_handles[i], NULL);
      else
        uv_close((uv_handle_t*) &pipe_write_handles[i], NULL);
    }

    exit(0);
  }

  /* Reset read and write counters */
  nrecv = 0;
  nsent = 0;
}