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
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ TCP ; 
 int /*<<< orphan*/  fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int,double) ; 
 double gbit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  loop ; 
 int max_read_sockets ; 
 int /*<<< orphan*/  nrecv_total ; 
 scalar_t__ start_time ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ type ; 
 scalar_t__ uv_now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv_update_time (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void read_show_stats(void) {
  int64_t diff;

  uv_update_time(loop);
  diff = uv_now(loop) - start_time;

  fprintf(stderr, "%s_pump%d_server: %.1f gbit/s\n",
          type == TCP ? "tcp" : "pipe",
          max_read_sockets,
          gbit(nrecv_total, diff));
  fflush(stderr);
}